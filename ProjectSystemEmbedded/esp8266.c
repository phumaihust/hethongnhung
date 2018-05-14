#define _ESP8266_RX_BUFFER_MAX   50

unsigned char ESP8266_rx_buffer[_ESP8266_RX_BUFFER_MAX];
unsigned int16 ESP8266_rx_index = 0;

int1 status_ok = 0;
int1 start_RST = 0;
int1 start_CIPSEND = 0;
int1 start_CONNECT = 0;
int1 start_CLOSED = 0;
int1 start_HTTP = 0;
int1 get_id_connect = 0;

unsigned char id_connect;

unsigned char flag_OK[] = "OK\r\n";
unsigned char flag_RST[] = "ready\r\n";
unsigned char flag_CIPSEND[] = "OK\r\n>";
//unsigned char flag_CONNECT[] = "CONNECT\r\n";
unsigned char flag_CLOSED[] = ",CLOSED\r\n";
unsigned char flag_HTTP[] = "GET / HTTP/1.1";
unsigned char flag_IPD[] = "+IPD,";

unsigned char flag_PIN1_TAT[]    = "GET /?pin=TAT";
unsigned char flag_PIN1_MUC1[]   = "GET /?pin=MUC1";
unsigned char flag_PIN1_MUC2[]   = "GET /?pin=MUC2";

unsigned char flag_OK_count = 0;
unsigned char flag_RST_count = 0;
unsigned char flag_CIPSEND_count = 0;
unsigned char flag_CONNECT_count = 0;
unsigned char flag_CLOSED_count = 0;
unsigned char flag_HTTP_count = 0;
unsigned char flag_IPD_count = 0;

unsigned char flag_PIN1_TAT_count = 0;
unsigned char flag_PIN1_MUC1_count = 0;
unsigned char flag_PIN1_MUC2_count = 0;

/***********************************************************************************************
Chuc nang   :      Kiem tra ket noi voi module Wifi ESP8266 da thanh cong chua
Tham so     :      Khong.
Tra ve      :      Khong.
***********************************************************************************************/
void ESP8266_AT()
{
   status_ok = 0;
   
   fprintf(ESP_STR, "AT\r\n");
   
   while (status_ok == 0) {}
   status_ok = 0;
}

/***********************************************************************************************
Chuc nang   :      Giu lenh reset module Wifi ESP8266 
Tham so     :      Khong.
Tra ve      :      Khong.
***********************************************************************************************/
void ESP8266_RST()
{
   start_RST = 0;
   
   fprintf(ESP_STR, "AT+RST\r\n");
   
   while (start_RST == 0) {}
   start_RST = 0;
}

/***********************************************************************************************
Chuc nang   :      Chon mode thiet lap cho module Wifi ESP8266 
Tham so     :      mode : chon che do cho mode esp8266 
                        mode = 1: Station mode
                        mode = 2: Access Point mode
                        mode = 3: Default both Station & AP mode
Tra ve      :      Khong.
***********************************************************************************************/
void ESP8266_CWMODE(unsigned char mode)
{
   status_ok = 0;
   
   fprintf(ESP_STR, "AT+CWMODE=%u\r\n", mode);
   
   while (status_ok == 0) {}
   status_ok = 0;
}

/***********************************************************************************************
Chuc nang   :      Ket noi WiFi cho module WiFi ESP8266 
Tham so     :      *ssid : ten Wifi muon ket noi
                   *pass : pass Wifi muon ket noi
Tra ve      :      Khong.
***********************************************************************************************/
void ESP8266_CWJAP(unsigned char *ssid, unsigned char *pass)
{
   status_ok = 0;
   
   fprintf(ESP_STR, "AT+CWJAP=\"%s\",\"%s\"\r\n", ssid, pass);
   
   while (status_ok == 0) {}
   status_ok = 0;
}

/***********************************************************************************************
Chuc nang   :      Dat dia chi IP tinh cho ESP8266 o mode Station 
Tham so     :      *ip_address: dia chi IP tinh
Tra ve      :      Khong.
***********************************************************************************************/
void ESP8266_CIPSTA(unsigned char* ip_address)
{
   status_ok = 0;
   
   fprintf(ESP_STR, "AT+CIPSTA=\"%s\"\r\n", ip_address);
   
   while (status_ok == 0) {}
   status_ok = 0;
}

/***********************************************************************************************
Chuc nang   :      Dat timeout cho 1 ket noi TCP server tu ESP8266 
Tham so     :      timeout: 1 -> 7200 (s)
                            0 - khong co timeout, not recommended
Tra ve      :      Khong.
***********************************************************************************************/
void ESP8266_CIPSTO(unsigned int16 timeout)
{
   status_ok = 0;
   
   fprintf(ESP_STR, "AT+CIPSTO=%lu\r\n", timeout);
   
   while (status_ok == 0) {}
   status_ok = 0;
}

/***********************************************************************************************
Chuc nang   :      kich hoat da ket noi (enable multiple connection) cho module Wifi ESP8266 
Tham so     :      mode : chon che do 
                        mode = 0: single connection
                        mode = 1: multiple connection
Tra ve      :      Khong.
***********************************************************************************************/
void ESP8266_CIPMUX(unsigned char mode)
{
   status_ok = 0;
   
   fprintf(ESP_STR, "AT+CIPMUX=%u\r\n", mode);
   
   while (status_ok == 0) {}
   status_ok = 0;
}

/***********************************************************************************************
Chuc nang   :      kich hoat server mo port cho module ESP8266 
Tham so     :      mode : chon che do 
                        mode = 0: xoa server
                        mode = 1: tao server
                   port : cong port giao tiep
Tra ve      :      Khong.
***********************************************************************************************/
void ESP8266_CIPSERVER(unsigned char mode, unsigned int16 port)
{
   status_ok = 0;
   
   fprintf(ESP_STR, "AT+CIPSERVER=%u,%lu\r\n", mode, port);
   
   while (status_ok == 0) {}
   status_ok = 0;
}

/***********************************************************************************************
Chuc nang   :      Thiet lap ket noi toi server (ESP8266 la client)
Tham so     :      - id:
                   - type:
                   - addr:
                   - port:
Tra ve      :      Khong.
***********************************************************************************************/
void ESP8266_CIPSTART(unsigned char id, unsigned char* type, unsigned char* ip_address, unsigned int16 port )
{
   status_ok = 0;
   
   fprintf(ESP_STR, "AT+CIPSTART=%u,\"%s\",\"%s\",%lu\r\n", id, type, ip_address, port);
   
   while (status_ok == 0) {}
   status_ok = 0;
}

/***********************************************************************************************
Chuc nang   :      Gui du lieu
Tham so     :      - id:
                   - type:
                   - addr:
                   - port:
Tra ve      :      Khong.
***********************************************************************************************/
void ESP8266_CIPSEND(unsigned char id, unsigned int16 length)
{
   start_CIPSEND = 0;
   
   fprintf(ESP_STR, "AT+CIPSEND=%c,%lu\r\n", id, length);
   
   while (start_CIPSEND == 0) {}
   start_CIPSEND = 0;
}




void ESP8266_clearBuffer()
{
   unsigned int16 i;
   ESP8266_rx_index = 0;
   
   for (i = 0; i < _ESP8266_RX_BUFFER_MAX; i++)
   {
      ESP8266_rx_buffer[i] = 0;
   }
}

void ESP8266_executeBuffer(unsigned char rx_data)
{
   ESP8266_rx_buffer[ESP8266_rx_index++] = rx_data;
   
   if (ESP8266_rx_index >= _ESP8266_RX_BUFFER_MAX)
      ESP8266_rx_index = 0;
   
   //-----------------------Xu ly cac ban tin mac dinh-------------------------
   
   //Response from AT
   if (rx_data == flag_OK[flag_OK_count])
   {
      flag_OK_count++;
      
      if (flag_OK_count == 4)
      {
         status_ok = 1;
         flag_OK_count = 0;
      }
      else
      {
         status_ok = 0;
      }
   }
   else
   {
      flag_OK_count = 0;
   }
   
   //Response from AT+RST
   if (rx_data == flag_RST[flag_RST_count])
   {
      flag_RST_count++;
      
      if (flag_RST_count == 7)
      {
         start_RST = 1;
         flag_RST_count = 0;
      }
      else
      {
         start_RST = 0;
      }
   }
   else
   {
      flag_RST_count = 0;
   }
   
   //Response from AT+CIPSEND
   if (rx_data == flag_CIPSEND[flag_CIPSEND_count])
   {
      flag_CIPSEND_count++;
      if (flag_CIPSEND_count == 5)
      {
         start_CIPSEND = 1;
         flag_CIPSEND_count = 0;
      }
      else
      {
         start_CIPSEND = 0;
      }
   }
   else
   {
      flag_CIPSEND_count = 0;
   }
   
   //Response from +IPD: when TCP client terminates connection
   if (rx_data == flag_CLOSED[flag_CLOSED_count])
   {
      flag_CLOSED_count++;
      if (flag_CLOSED_count == 9)
      {
         start_CLOSED = 1;
         
         flag_CLOSED_count = 0;
      }
      else
      {
         start_CLOSED = 0;
      }
   }
   else
   {
      flag_CONNECT_count = 0;
   }
   
   //Response from...
   if (rx_data == flag_HTTP[flag_HTTP_count])
   {
      flag_HTTP_count++;
      if (flag_HTTP_count == 14)
      {         
         start_HTTP = 1;
         is_updated = 0;
         flag_HTTP_count = 0;
      }
   }
   else
   {
      flag_HTTP_count = 0;
   }
   
   if (get_id_connect)
   {
      get_id_connect = 0;
      id_connect = rx_data;
   }
   
   if (rx_data == flag_IPD[flag_IPD_count])
   {
      flag_IPD_count++;
      if (flag_IPD_count == 5)
      {         
         start_CONNECT = 1;
         get_id_connect = 1;
         flag_IPD_count = 0;
      }
   }
   else
   {
      flag_IPD_count = 0;
   }
   
   
   
   //---------------------------Xu ly cac ban tin tu trang web-----------------
   
   //Xu ly khi co du lieu bat PIN 1
   if (rx_data == flag_PIN1_TAT[flag_PIN1_TAT_count])
   {
      flag_PIN1_TAT_count++;
      if (flag_PIN1_TAT_count == 13)
      {
         pin1_status = 0;
         
         flag_PIN1_TAT_count = 0;
         is_updated = 0;
      }
   }
   else
   {
      flag_PIN1_TAT_count = 0;
   }
   
   //Xu ly khi co du lieu tat PIN 1
   if (rx_data == flag_PIN1_MUC1[flag_PIN1_MUC1_count])
   {
      flag_PIN1_MUC1_count++;
      if (flag_PIN1_MUC1_count == 14)
      {
         pin1_status = 1;
         
         flag_PIN1_MUC1_count = 0;
         is_updated = 0;
      }
   }
   else
   {
      flag_PIN1_MUC1_count = 0;
   }
   
   if (rx_data == flag_PIN1_MUC2[flag_PIN1_MUC2_count])
   {
      flag_PIN1_MUC2_count++;
      if (flag_PIN1_MUC2_count == 14)
      {
         pin1_status = 2;
         
         flag_PIN1_MUC2_count = 0;
         is_updated = 0;
      }
   }
   else
   {
      flag_PIN1_MUC2_count = 0;
   }
}
