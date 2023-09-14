struct m_hdr{
	struct mbuf *mh_next;
	struct mbuf *mh_nextpkt;
	int mh_len;
	caddr_t mh_data;
	short mh_type;
	short mh_type;
}

struct pkhdr{
	int len;
	struct ifnet *rvcif;
}

struct m_ext{
	caddr_t ext_buf;
	void (*ext_free) ();
	u_int ext_size;
}

struct mbuf{
	struct m_hdr m_hdr;
	union {
		struct {
			struct pkthdr MH_pkthdr;
			union {
				struct m_ext MH_ext;
				char MH_databuf(MHLEN);
			} MH_dat;
		} MH;
		char M_databuf[MLEN];
	} M_dat;
}