#ifndef _MOUSE_H_
#define _MOUSE_H_

#include "minixforce.h"
#include "i8042.h"

/** @defgroup mouse mouse
 * @{
 *
 * Functions to interact with the i8042 KBC for mouse.
 */

/**
 * @brief Subscribes interrupts and enables data report.
 *
 * @param bit_no Address of memory to be initialized with the mouse
 *               peripheral interface controller bit number to be set
 *               in the mask returned upon an interrupt
 * 
 * @return Return 0 upon success and non-zero otherwise
 */
int mouse_subscribe_int(uint16_t *bit__no);

/**
 * @brief Unsubscribes interrupts and disables data report.
 *
 * @return Return 0 upon success and non-zero otherwise
 */
int mouse_unsubscribe_int();

/** 
 * @brief Reads the content of the Output Buffer
 * 
 * Checks if there is any timeout or parity error and if the
 * information is coming from the mouse
 * 
 * Polls the Status Register until the Output Buffer is full
 * 
 * @param content Adddress of memory where the content read from the
 *                Output Buffer will be written to
 * 
 * @return Return 0 upon success and non-zero otherwise
 */
int mouse_read_out_buf(uint8_t *content);

/** 
 * @brief Writes command to specified port of the KBC
 * 
 * Polls the Status Register until the Input Buffer is empty
 * 
 * @param port Address of the port the command is being written to
 * @param cmd Command that will be written to the KBC
 * 
 * @return Return 0 upon success and non-zero otherwise
 */
int kbc_write(port_t port, uint8_t cmd);

/** 
 * @brief Writes byte to mouse
 * 
 * Sends write byte to mouse command to the control register
 * 
 * Sends mouse command to the Input Buffer
 * 
 * Receives acknowledgement and checks if the acknowledgement is correct
 * 
 * If not correct, tries again one more time
 * 
 * @param cmd Command that will be written to the mouse
 * 
 * @return Return 0 upon success and non-zero otherwise
 */
int kbc_write_mouse_command(uint8_t cmd);

/** 
 * @brief Receives an incomplete packet and parses it
 * 
 * Packet contains only the 3 byte array
 * 
 * Checks the bits of the first byte and completes the packet data
 * 
 * @param pp Memory address containing the incomplete packet
 * 
 * @return Return 0 upon success and non-zero otherwise
 */
int mouse_parse_packet(struct packet *pp);


/** 
 * @brief 
 * this function detects the events that ocurrer and are important
 * for the state machine
 * 
 * @param 
 * pp Memory address containing a complte packet
 *     
 * @return Return 0 upon success and non-zero otherwise
 */
struct mouse_ev *mouse_event_detect(struct packet *pp);

/** 
 * @brief 
 * Detect if the left button was pressed and the mouse movement. \n
 * If the left button was pressed, if puts mouse state in "fire". \n
 * if theres moviment, changes crosshair coordinates, calling
 * updateMouse function.
 * 
 * @param 
 * pp Memory address containing a complte packet
 * length of the movement
 * tolerance to the x aceptend
 *     
 */
void weapon(struct packet *pp);

/** 
 * @brief 
 * It updates the crosshair position, base on the movement of the mouse. 
 * 
 * @param 
 * pp Memory address containing a complte packet
 * length of the movement tolerance to the x aceptend
 */
void updateMouse(struct packet *pp);

/** 
 * @brief 
 * To clear code
 * @return mouse identification number
 */
uint32_t getmouse_id();

/** 
 * @brief 
 * To clear code
 * @return byte on the buffer
 */
uint8_t getoneByte();

/**@}*/

#endif
