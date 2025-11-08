#ifndef _H_HCI_
#define _H_HCI_

typedef enum
{
    HCI_HDR_TYPE_ACK = 0,
    HCI_HDR_TYPE_CMD = 1,
    HCI_HDR_TYPE_ACL = 2,
    HCI_HDR_TYPE_SYN = 3,
    HCI_HDR_TYPE_EVT = 4,
    HCI_HDR_TYPE_VENDOR = 14,
    HCI_HDR_TYPE_LINK_CONTROL = 15,
} hci_hdr_type_t;

#endif // _H_HCI_
