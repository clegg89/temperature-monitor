/*
 * @file root-ca.cpp
 *
 * @author C. Smith
 */

#include "root-ca.hpp"

/*
 * TODO I'm not fond of this solution. It will work for now.
 *
 * These are binary representations of the Root CA certificate and it's
 * length (the Root CA is required, and should be self-signed). To obtain
 * the Root CA, use openssl to find the issure of the last Certificate in
 * the chain sent by the client:
 *    
 *    openssl s_client -showcerts -connect ${SERVERNAME}:${SERVERPORT} < /dev/null 2> /dev/null | \
 *      openssl x509 -noout -text
 *
 * The issuer of the last certificate should be the Root CA. For example
 * "Addtrust External CA Root." The certificate should be somewhere on your
 * system (location will vary). You can typically export it from your browser
 * in some fashion. You will want to get the certificate into DER form. If it
 * is in PEM format you can use the following command:
 *
 *    openssl x509 -in ${ROOTCA}.pem -out ${ROOTCA}.der -outform DER
 *
 * Finally you can create a C file which will contain the array and length
 * using xxd -i:
 *
 *    xxd -i ${ROOTCA}.der > ca-certificate.c
 *
 * Change the name of the array and length to the names below and place
 * the file in the src directory (same directory as this file).
 *
 * Possible future improvements:
 *   - Automating at least a portion of the process. It would be difficult
 *     to automate obtaining the Root CA as that varies based on browser
 *     and system.
 *   - Using SPIFFS to store the CA certificate, allowing for certificate
 *     updates without the need to upgrade the entire firmware.
 */

/** Root CA in x509 DER format */
static const uint8_t ca_certificate[] = {
  0x30, 0x82, 0x04, 0x36, 0x30, 0x82, 0x03, 0x1e, 0xa0, 0x03, 0x02, 0x01,
  0x02, 0x02, 0x01, 0x01, 0x30, 0x0d, 0x06, 0x09, 0x2a, 0x86, 0x48, 0x86,
  0xf7, 0x0d, 0x01, 0x01, 0x05, 0x05, 0x00, 0x30, 0x6f, 0x31, 0x0b, 0x30,
  0x09, 0x06, 0x03, 0x55, 0x04, 0x06, 0x13, 0x02, 0x53, 0x45, 0x31, 0x14,
  0x30, 0x12, 0x06, 0x03, 0x55, 0x04, 0x0a, 0x13, 0x0b, 0x41, 0x64, 0x64,
  0x54, 0x72, 0x75, 0x73, 0x74, 0x20, 0x41, 0x42, 0x31, 0x26, 0x30, 0x24,
  0x06, 0x03, 0x55, 0x04, 0x0b, 0x13, 0x1d, 0x41, 0x64, 0x64, 0x54, 0x72,
  0x75, 0x73, 0x74, 0x20, 0x45, 0x78, 0x74, 0x65, 0x72, 0x6e, 0x61, 0x6c,
  0x20, 0x54, 0x54, 0x50, 0x20, 0x4e, 0x65, 0x74, 0x77, 0x6f, 0x72, 0x6b,
  0x31, 0x22, 0x30, 0x20, 0x06, 0x03, 0x55, 0x04, 0x03, 0x13, 0x19, 0x41,
  0x64, 0x64, 0x54, 0x72, 0x75, 0x73, 0x74, 0x20, 0x45, 0x78, 0x74, 0x65,
  0x72, 0x6e, 0x61, 0x6c, 0x20, 0x43, 0x41, 0x20, 0x52, 0x6f, 0x6f, 0x74,
  0x30, 0x1e, 0x17, 0x0d, 0x30, 0x30, 0x30, 0x35, 0x33, 0x30, 0x31, 0x30,
  0x34, 0x38, 0x33, 0x38, 0x5a, 0x17, 0x0d, 0x32, 0x30, 0x30, 0x35, 0x33,
  0x30, 0x31, 0x30, 0x34, 0x38, 0x33, 0x38, 0x5a, 0x30, 0x6f, 0x31, 0x0b,
  0x30, 0x09, 0x06, 0x03, 0x55, 0x04, 0x06, 0x13, 0x02, 0x53, 0x45, 0x31,
  0x14, 0x30, 0x12, 0x06, 0x03, 0x55, 0x04, 0x0a, 0x13, 0x0b, 0x41, 0x64,
  0x64, 0x54, 0x72, 0x75, 0x73, 0x74, 0x20, 0x41, 0x42, 0x31, 0x26, 0x30,
  0x24, 0x06, 0x03, 0x55, 0x04, 0x0b, 0x13, 0x1d, 0x41, 0x64, 0x64, 0x54,
  0x72, 0x75, 0x73, 0x74, 0x20, 0x45, 0x78, 0x74, 0x65, 0x72, 0x6e, 0x61,
  0x6c, 0x20, 0x54, 0x54, 0x50, 0x20, 0x4e, 0x65, 0x74, 0x77, 0x6f, 0x72,
  0x6b, 0x31, 0x22, 0x30, 0x20, 0x06, 0x03, 0x55, 0x04, 0x03, 0x13, 0x19,
  0x41, 0x64, 0x64, 0x54, 0x72, 0x75, 0x73, 0x74, 0x20, 0x45, 0x78, 0x74,
  0x65, 0x72, 0x6e, 0x61, 0x6c, 0x20, 0x43, 0x41, 0x20, 0x52, 0x6f, 0x6f,
  0x74, 0x30, 0x82, 0x01, 0x22, 0x30, 0x0d, 0x06, 0x09, 0x2a, 0x86, 0x48,
  0x86, 0xf7, 0x0d, 0x01, 0x01, 0x01, 0x05, 0x00, 0x03, 0x82, 0x01, 0x0f,
  0x00, 0x30, 0x82, 0x01, 0x0a, 0x02, 0x82, 0x01, 0x01, 0x00, 0xb7, 0xf7,
  0x1a, 0x33, 0xe6, 0xf2, 0x00, 0x04, 0x2d, 0x39, 0xe0, 0x4e, 0x5b, 0xed,
  0x1f, 0xbc, 0x6c, 0x0f, 0xcd, 0xb5, 0xfa, 0x23, 0xb6, 0xce, 0xde, 0x9b,
  0x11, 0x33, 0x97, 0xa4, 0x29, 0x4c, 0x7d, 0x93, 0x9f, 0xbd, 0x4a, 0xbc,
  0x93, 0xed, 0x03, 0x1a, 0xe3, 0x8f, 0xcf, 0xe5, 0x6d, 0x50, 0x5a, 0xd6,
  0x97, 0x29, 0x94, 0x5a, 0x80, 0xb0, 0x49, 0x7a, 0xdb, 0x2e, 0x95, 0xfd,
  0xb8, 0xca, 0xbf, 0x37, 0x38, 0x2d, 0x1e, 0x3e, 0x91, 0x41, 0xad, 0x70,
  0x56, 0xc7, 0xf0, 0x4f, 0x3f, 0xe8, 0x32, 0x9e, 0x74, 0xca, 0xc8, 0x90,
  0x54, 0xe9, 0xc6, 0x5f, 0x0f, 0x78, 0x9d, 0x9a, 0x40, 0x3c, 0x0e, 0xac,
  0x61, 0xaa, 0x5e, 0x14, 0x8f, 0x9e, 0x87, 0xa1, 0x6a, 0x50, 0xdc, 0xd7,
  0x9a, 0x4e, 0xaf, 0x05, 0xb3, 0xa6, 0x71, 0x94, 0x9c, 0x71, 0xb3, 0x50,
  0x60, 0x0a, 0xc7, 0x13, 0x9d, 0x38, 0x07, 0x86, 0x02, 0xa8, 0xe9, 0xa8,
  0x69, 0x26, 0x18, 0x90, 0xab, 0x4c, 0xb0, 0x4f, 0x23, 0xab, 0x3a, 0x4f,
  0x84, 0xd8, 0xdf, 0xce, 0x9f, 0xe1, 0x69, 0x6f, 0xbb, 0xd7, 0x42, 0xd7,
  0x6b, 0x44, 0xe4, 0xc7, 0xad, 0xee, 0x6d, 0x41, 0x5f, 0x72, 0x5a, 0x71,
  0x08, 0x37, 0xb3, 0x79, 0x65, 0xa4, 0x59, 0xa0, 0x94, 0x37, 0xf7, 0x00,
  0x2f, 0x0d, 0xc2, 0x92, 0x72, 0xda, 0xd0, 0x38, 0x72, 0xdb, 0x14, 0xa8,
  0x45, 0xc4, 0x5d, 0x2a, 0x7d, 0xb7, 0xb4, 0xd6, 0xc4, 0xee, 0xac, 0xcd,
  0x13, 0x44, 0xb7, 0xc9, 0x2b, 0xdd, 0x43, 0x00, 0x25, 0xfa, 0x61, 0xb9,
  0x69, 0x6a, 0x58, 0x23, 0x11, 0xb7, 0xa7, 0x33, 0x8f, 0x56, 0x75, 0x59,
  0xf5, 0xcd, 0x29, 0xd7, 0x46, 0xb7, 0x0a, 0x2b, 0x65, 0xb6, 0xd3, 0x42,
  0x6f, 0x15, 0xb2, 0xb8, 0x7b, 0xfb, 0xef, 0xe9, 0x5d, 0x53, 0xd5, 0x34,
  0x5a, 0x27, 0x02, 0x03, 0x01, 0x00, 0x01, 0xa3, 0x81, 0xdc, 0x30, 0x81,
  0xd9, 0x30, 0x1d, 0x06, 0x03, 0x55, 0x1d, 0x0e, 0x04, 0x16, 0x04, 0x14,
  0xad, 0xbd, 0x98, 0x7a, 0x34, 0xb4, 0x26, 0xf7, 0xfa, 0xc4, 0x26, 0x54,
  0xef, 0x03, 0xbd, 0xe0, 0x24, 0xcb, 0x54, 0x1a, 0x30, 0x0b, 0x06, 0x03,
  0x55, 0x1d, 0x0f, 0x04, 0x04, 0x03, 0x02, 0x01, 0x06, 0x30, 0x0f, 0x06,
  0x03, 0x55, 0x1d, 0x13, 0x01, 0x01, 0xff, 0x04, 0x05, 0x30, 0x03, 0x01,
  0x01, 0xff, 0x30, 0x81, 0x99, 0x06, 0x03, 0x55, 0x1d, 0x23, 0x04, 0x81,
  0x91, 0x30, 0x81, 0x8e, 0x80, 0x14, 0xad, 0xbd, 0x98, 0x7a, 0x34, 0xb4,
  0x26, 0xf7, 0xfa, 0xc4, 0x26, 0x54, 0xef, 0x03, 0xbd, 0xe0, 0x24, 0xcb,
  0x54, 0x1a, 0xa1, 0x73, 0xa4, 0x71, 0x30, 0x6f, 0x31, 0x0b, 0x30, 0x09,
  0x06, 0x03, 0x55, 0x04, 0x06, 0x13, 0x02, 0x53, 0x45, 0x31, 0x14, 0x30,
  0x12, 0x06, 0x03, 0x55, 0x04, 0x0a, 0x13, 0x0b, 0x41, 0x64, 0x64, 0x54,
  0x72, 0x75, 0x73, 0x74, 0x20, 0x41, 0x42, 0x31, 0x26, 0x30, 0x24, 0x06,
  0x03, 0x55, 0x04, 0x0b, 0x13, 0x1d, 0x41, 0x64, 0x64, 0x54, 0x72, 0x75,
  0x73, 0x74, 0x20, 0x45, 0x78, 0x74, 0x65, 0x72, 0x6e, 0x61, 0x6c, 0x20,
  0x54, 0x54, 0x50, 0x20, 0x4e, 0x65, 0x74, 0x77, 0x6f, 0x72, 0x6b, 0x31,
  0x22, 0x30, 0x20, 0x06, 0x03, 0x55, 0x04, 0x03, 0x13, 0x19, 0x41, 0x64,
  0x64, 0x54, 0x72, 0x75, 0x73, 0x74, 0x20, 0x45, 0x78, 0x74, 0x65, 0x72,
  0x6e, 0x61, 0x6c, 0x20, 0x43, 0x41, 0x20, 0x52, 0x6f, 0x6f, 0x74, 0x82,
  0x01, 0x01, 0x30, 0x0d, 0x06, 0x09, 0x2a, 0x86, 0x48, 0x86, 0xf7, 0x0d,
  0x01, 0x01, 0x05, 0x05, 0x00, 0x03, 0x82, 0x01, 0x01, 0x00, 0xb0, 0x9b,
  0xe0, 0x85, 0x25, 0xc2, 0xd6, 0x23, 0xe2, 0x0f, 0x96, 0x06, 0x92, 0x9d,
  0x41, 0x98, 0x9c, 0xd9, 0x84, 0x79, 0x81, 0xd9, 0x1e, 0x5b, 0x14, 0x07,
  0x23, 0x36, 0x65, 0x8f, 0xb0, 0xd8, 0x77, 0xbb, 0xac, 0x41, 0x6c, 0x47,
  0x60, 0x83, 0x51, 0xb0, 0xf9, 0x32, 0x3d, 0xe7, 0xfc, 0xf6, 0x26, 0x13,
  0xc7, 0x80, 0x16, 0xa5, 0xbf, 0x5a, 0xfc, 0x87, 0xcf, 0x78, 0x79, 0x89,
  0x21, 0x9a, 0xe2, 0x4c, 0x07, 0x0a, 0x86, 0x35, 0xbc, 0xf2, 0xde, 0x51,
  0xc4, 0xd2, 0x96, 0xb7, 0xdc, 0x7e, 0x4e, 0xee, 0x70, 0xfd, 0x1c, 0x39,
  0xeb, 0x0c, 0x02, 0x51, 0x14, 0x2d, 0x8e, 0xbd, 0x16, 0xe0, 0xc1, 0xdf,
  0x46, 0x75, 0xe7, 0x24, 0xad, 0xec, 0xf4, 0x42, 0xb4, 0x85, 0x93, 0x70,
  0x10, 0x67, 0xba, 0x9d, 0x06, 0x35, 0x4a, 0x18, 0xd3, 0x2b, 0x7a, 0xcc,
  0x51, 0x42, 0xa1, 0x7a, 0x63, 0xd1, 0xe6, 0xbb, 0xa1, 0xc5, 0x2b, 0xc2,
  0x36, 0xbe, 0x13, 0x0d, 0xe6, 0xbd, 0x63, 0x7e, 0x79, 0x7b, 0xa7, 0x09,
  0x0d, 0x40, 0xab, 0x6a, 0xdd, 0x8f, 0x8a, 0xc3, 0xf6, 0xf6, 0x8c, 0x1a,
  0x42, 0x05, 0x51, 0xd4, 0x45, 0xf5, 0x9f, 0xa7, 0x62, 0x21, 0x68, 0x15,
  0x20, 0x43, 0x3c, 0x99, 0xe7, 0x7c, 0xbd, 0x24, 0xd8, 0xa9, 0x91, 0x17,
  0x73, 0x88, 0x3f, 0x56, 0x1b, 0x31, 0x38, 0x18, 0xb4, 0x71, 0x0f, 0x9a,
  0xcd, 0xc8, 0x0e, 0x9e, 0x8e, 0x2e, 0x1b, 0xe1, 0x8c, 0x98, 0x83, 0xcb,
  0x1f, 0x31, 0xf1, 0x44, 0x4c, 0xc6, 0x04, 0x73, 0x49, 0x76, 0x60, 0x0f,
  0xc7, 0xf8, 0xbd, 0x17, 0x80, 0x6b, 0x2e, 0xe9, 0xcc, 0x4c, 0x0e, 0x5a,
  0x9a, 0x79, 0x0f, 0x20, 0x0a, 0x2e, 0xd5, 0x9e, 0x63, 0x26, 0x1e, 0x55,
  0x92, 0x94, 0xd8, 0x82, 0x17, 0x5a, 0x7b, 0xd0, 0xbc, 0xc7, 0x8f, 0x4e,
  0x86, 0x04
};
static const unsigned int ca_certificate_len = 1082;

const std::vector<uint8_t> RootCaCertificate(ca_certificate, ca_certificate + ca_certificate_len);
