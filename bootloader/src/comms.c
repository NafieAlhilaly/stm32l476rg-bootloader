#include "comms.h"
#include "string.h"

typedef enum comms_state_t
{
  CommsState_Length,
  CommsState_Data,
  CommsState_CRC,
} comms_state_t;

static comms_state_t state = CommsState_Length;
static uint8_t data_recieved_count = 0;

static comms_packet_t tmp_packet = {.length = 0, .data = {0}, .crc = 0};
static comms_packet_t retx_packet = {.length = 1, .data = {0}, .crc = 0};
static comms_packet_t ack_packet = {.length = 1, .data = {0}, .crc = 0};
static comms_packet_t last_transmitted_packet = {.length = 0, .data = {0}, .crc = 0};

static comms_packet_t packet_buffer[PACKET_BUFFER_LENGTH];
static uint32_t packet_read_index = 0;
static uint32_t packet_write_index = 0;
static uint32_t packet_buffer_mask = PACKET_BUFFER_LENGTH;

static bool comms_is_single_byte_packet(const comms_packet_t *packet,
                                        uint8_t byte)
{
  if (packet->length != 1)
  {
    return false;
  }

  if (packet->data[0] != byte)
  {
    return false;
  }

  for (uint8_t i = 1; i < PACKET_DATA_LENGTH; i++)
  {
    if (packet->data[i] != 0xff)
    {
      return false;
    }
  }

  return true;
}

void comms_setup(void)
{
  retx_packet.data[0] = PACKET_RETX_DATA0;
  for (uint8_t i = 1; i < PACKET_DATA_LENGTH; i++)
  {
    retx_packet.data[i] = 0xff;
  }
  retx_packet.crc = comms_compute_crc(&retx_packet);

  ack_packet.data[0] = PACKET_ACK_DATA0;
  for (uint8_t i = 1; i < PACKET_DATA_LENGTH; i++)
  {
    ack_packet.data[i] = 0xff;
  }
  ack_packet.crc = comms_compute_crc(&ack_packet);
}
void comms_update(void)
{
  while (uart_data_available())
  {
    switch (state)
    {
    case CommsState_Length:
    {
      tmp_packet.length = uart_read_byte();
      state = CommsState_Data;
    }
    break;
    case CommsState_Data:
    {
      tmp_packet.data[data_recieved_count++] = uart_read_byte();
      if (data_recieved_count >= PACKET_DATA_LENGTH)
      {
        data_recieved_count = 0;
        state = CommsState_CRC;
      }
    }
    break;
    case CommsState_CRC:
    {
      tmp_packet.crc = uart_read_byte();

      if (tmp_packet.crc != comms_compute_crc(&tmp_packet))
      {
        comms_write(&retx_packet);
        state = CommsState_Length;
        break;
      }
      if (comms_is_single_byte_packet(&tmp_packet, PACKET_RETX_DATA0))
      {
        comms_write(&retx_packet);
        state = CommsState_Length;
        break;
      }
      if (comms_is_single_byte_packet(&tmp_packet, PACKET_ACK_DATA0))
      {
        state = CommsState_Length;
        break;
      }

      uint32_t next_write_index = (packet_write_index + 1) & packet_buffer_mask;

      memcpy(&packet_buffer[packet_write_index], &tmp_packet, sizeof(comms_packet_t));
      packet_write_index = next_write_index;
      comms_write(&ack_packet);
      state = CommsState_Length;
    }
    break;

    default:
    {
      state = CommsState_Length;
    }
    }
  }
}

bool comms_available(void) { return packet_read_index != packet_write_index; }
void comms_write(comms_packet_t* packet)
{
  uart_write((uint8_t*)packet, PACKET_LENGTH);
  memcpy(&packet, &last_transmitted_packet,sizeof(comms_packet_t));
}
void comms_read(comms_packet_t *packet)
{
  memcpy(packet, &packet_buffer[packet_read_index],sizeof(comms_packet_t));
  packet_read_index = (packet_write_index + 1) & packet_buffer_mask;
}

uint8_t comms_compute_crc(comms_packet_t *packet)
{
  return crc8((uint8_t*)packet, PACKET_LENGTH - PACKET_CRC_BYTES);
}
