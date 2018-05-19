***** SERVER DISCOVER *****
char serv_discovr_req[1500];
struct e_hdr s_d_hdr;
s_d_hdr.dest = 0xff;			// broadcast
s_d_hdr.source = me;

get_my_mac(mac)
