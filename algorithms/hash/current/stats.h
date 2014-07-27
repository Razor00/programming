#ifndef __STATS_H
#define __STATS_H

#define MAX_STR_LEN 10

struct PKT_STATS {
    unsigned int l2_pkts;
    unsigned int ip_pkts;
    unsigned int tcp_pkts;
};

typedef struct PKT_STATS pkt_stats;

struct STATS {
    char mac_type;
    pkt_stats in;
    pkt_stats out;
}__attribute__((packed));

typedef struct STATS stats;

enum MAC_TYPE { BROADCAST = 0, MULTICAST = 1, UNICAST = 2 };


#endif
