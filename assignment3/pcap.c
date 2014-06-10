#include <stdio.h>
#include <pcap.h>
#include <string.h>
#include <stdlib.h>
#include <linux/ip.h>
#include <netinet/ether.h>
#include <arpa/inet.h>
#include <netinet/in.h>

struct ip 
{
        u_char version;      			/* version of IP */
        u_char typeofservice;      		/* type of service */
        u_short totallength;     		/* total length */
        u_short identification;      		/* identification */
        u_short offset;     			/* fragment offset field */
	#define DF 0x4000                 	/* dont fragment flag        */
	#define MF 0x2000                 	/* more fragments flag       */
	#define OFFMASK 0x1fff            	/* mask for fragmenting bits */
        u_char ttl;      			/* time to live */
        u_char protocol;        		/* protocol */
        u_short checksum;     			/* checksum */
        struct in_addr source;			/* Source IP Address */
        struct in_addr destination;		/* Destination IP Address */
};

struct eth
{

	const struct ether_addr destination; 	/*the destination host address */
	const struct ether_addr source; 	/*the source host address */
	u_short type; 				/*to check if its ip etc */

};

struct arp
{ 
    	u_int16_t htype;    		/* Hardware Type           */ 
    	u_int16_t ptype;    		/* Protocol Type           */ 
    	u_char hlen;        		/* Hardware Address Length */ 
    	u_char plen;        		/* Protocol Address Length */ 
    	u_int16_t operation;     	/* Operation Code          */ 
    	u_char senderhardware[6];      	/* Sender hardware address */ 
    	u_char senderip[4];      	/* Sender IP address       */ 
    	u_char targethardware[6];      	/* Target hardware address */ 
    	u_char targetip[4];      	/* Target IP address       */ 
};

struct tcp 
{
        u_short source;   		/* source port */
        u_short destination;   		/* destination port */
        u_int32_t sequence;       	/* sequence number */
        u_int32_t ack;       		/* acknowledgement number */
        u_char th_offx2;    		/* data offset, rsvd */
        u_char flags;			/* TCP FLAGS */
    	#define FIN 0x01
    	#define SYN 0x02
    	#define RST 0x04
    	#define PUSH 0x08
    	#define ACK 0x10
    	#define URG 0x20
    	#define ECE 0x40
    	#define CWR 0x80
    	#define TH_FLAGS (FIN|SYN|RST|ACK|URG|ECE|CWR)
        u_short window;     		/* window */
        u_short th_sum;     		/* checksum */
        u_short th_urp;     		/* urgent pointer */
};



int main(int argc, char *argv[])
{
	char file[20];
	strcpy(file,argv[1]);
	char errbuff[PCAP_ERRBUF_SIZE];
	pcap_t * handle;
	handle=pcap_open_offline(file,errbuff);
	struct pcap_pkthdr *header;
	const u_char *data;
	const char *temp;
	struct eth *ethernetheader;
	struct ip *ipheader;
	struct arp *arpheader;
	struct tcp *tcpheader;
	
	int i;
	int no_of_packets=0;
	int total_bytes=0;
	float total_time;
	int total_time_milli;
	long int time0;
	long int time0_milli;
	long int time1;
	long int time1_milli;
	int returnvalue;
	int majorversion;
	int minorversion;
	int snapshot_size;
	int datalink;

	majorversion=pcap_major_version(handle);
	minorversion=pcap_minor_version(handle);
	snapshot_size=pcap_snapshot(handle);
	datalink=pcap_datalink(handle);
	printf("Global Header Details :\n\n");
	printf("Version Number:%d.%d\n",majorversion,minorversion);
	printf("Snapshot Size:%d bytes\n",snapshot_size);
	printf("Data Link Type:%d\n",datalink);
	temp=pcap_datalink_val_to_name(datalink);
	printf("Data Link Type Name:");
	puts(temp);
	printf("\n\n");
	while(returnvalue =pcap_next_ex(handle, &header, &data) >=0)
	{
		no_of_packets++;
		if(no_of_packets==1)
		{
			time0=header->ts.tv_sec;
			time0_milli=header->ts.tv_usec;
		}
		printf("Packet Number :%d\n",no_of_packets);
		printf("Packet Size :%d bytes\n",header->len);
		printf("Packet Size captured in file :%d bytes\n",header->caplen);
		total_bytes=total_bytes+header->len;
		printf("Total Bytes:%d\n",total_bytes);
		printf("Packet capture time :%ld:%ld seconds\n",header->ts.tv_sec,header->ts.tv_usec);
		ethernetheader=(struct eth *)(data);
		printf("Source MAC: %s\n", ether_ntoa(&ethernetheader->source));
    		printf("Destination MAC: %s\n", ether_ntoa(&ethernetheader->destination));
		if(ntohs(ethernetheader->type)==0x0800)
		{
			printf("Packet Type: IPv4\n");
			ipheader=(struct ip *)(data+sizeof(struct eth));
			printf("Source IP Address: %s \n",inet_ntoa(ipheader->source));
			printf("Destination IP Address: %s \n",inet_ntoa(ipheader->destination));
			printf("Time to Live:%d\n",ipheader->ttl);
			if(ipheader->protocol==6)
			{
				printf("Protocol: TCP\n");
				tcpheader=(struct tcp *)(data + sizeof(struct eth) + sizeof(struct ip));
				printf("Source Port: %d\n",ntohs(tcpheader->source));
				printf("Destination Port: %d\n",ntohs(tcpheader->destination));
				printf("Sequence Number: %u\n",(unsigned int)ntohl(tcpheader->sequence));
				printf("Acknowledgement Number: %u\n",(unsigned int)ntohl(tcpheader->ack));
				if(tcpheader->flags & TH_FLAGS)
				{
					printf("Flags Present: ");
					if (tcpheader->flags & ECE)
					{
        					printf("ECE ");
    					}
    					if (tcpheader->flags & ACK)
					{
        					printf("ACK ");
   					}
					if (tcpheader->flags & SYN)
					{
        					printf("SYN ");
   					}
					if (tcpheader->flags & FIN)
					{
        					printf("FIN ");
   					}
					if (tcpheader->flags & RST)
					{
        					printf("RST ");
   					}
					if (tcpheader->flags & PUSH)
					{
        					printf("PUSH ");
   					}
					if (tcpheader->flags & URG)
					{
        					printf("URG ");
   					}
					if (tcpheader->flags & CWR)
					{
        					printf("CWR ");
   					}
					printf("\n");
				}
				else
				{
					printf("No Flags Present\n");
				}
				printf("Window Size Value: %d\n",ntohs(tcpheader->window));				
				
			}
		}
		if(ntohs(ethernetheader->type)==0x0806)
		{
			printf("Packet Type: ARP\n");
			arpheader = (struct arp *)(data+sizeof(struct eth));
			if(ntohs(arpheader->operation)==1)
			{
				printf("Operation: ARP Request\n");
			}
			else
			{
				printf("Operation: ARP Reply\n");
			}
			printf("Source IP Address :");
			for(i=0; i<4;i++)
			{
        			printf("%d.", arpheader->senderip[i]);
			} 
			printf("\n");
			printf("Destination IP Address :");
			for(i=0; i<4;i++)
			{
        			printf("%d.", arpheader->targetip[i]);
			} 
			
		}
		
		
		
		time1=header->ts.tv_sec;
		time1_milli=header->ts.tv_usec;
		printf("\n\n");
	}
	total_time=time1-time0;
	total_time_milli=time1_milli-time0_milli;
	printf("Summary:-\n");
	printf("Total Number of packets captured: %d\n",no_of_packets);
	printf("Total Number of Bytes captured: %d Bytes\n",total_bytes);
	printf("Average Packet Size: %f Bytes\n",(float)total_bytes/no_of_packets);
	total_time_milli=total_time_milli/1000;
	total_time=total_time+(total_time_milli/1000.0);
	printf("Total Capture Duration: %f sec\n",total_time);
	printf("Data Byte Rate: %f bytes/sec\n",total_bytes/total_time);
	printf("Data Bit Rate: %f bits/sec\n",total_bytes*8/total_time);
	printf("Average Packet Rate: %d\n\n",no_of_packets/(int)total_time);
	return 0;
}
