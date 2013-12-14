/* h8-3052-iodef.h */
/* H8300H���꡼��3052�γƥ쥸����������� */

/*   �������Ƥ���쥸����̾�򤢤������ѿ��Τ褦�˻��ѤǤ��� */
/*     �㡧P1DDR = a; a = P1DR; �Τ褦�˻Ȥ��� */ 

/*   ����ξܺ٤�PDF�ޥ˥奢��(rjj09b0335_3052bhm.pdf)���ȤΤ��� */
/*   ����2008ǯ4��1�� �º� */

/* SCI�ˤĤ��Ƥϥ쥸����̾�θ�˥���ͥ��ֹ���ղä��Ƥ��� */
/*   �㡧BRR0 (â��SCMR�����ϥ���ͥ�0��ͭ�Τ����ղä���) */

/* �⡼�ɥ���ȥ���쥸���� */
#define MDCR (*(volatile unsigned char *)0xfffff1)
/* �����ƥॳ��ȥ���쥸���� */
#define SYSCR (*(volatile unsigned char *)0xfffff2)

/* ��¢ROM��Ϣ */
/* �ե�å�����ꥳ��ȥ���쥸����1 */
#define FLMCR1 (*(volatile unsigned char *)0xffff40)
/* �ե�å�����ꥳ��ȥ���쥸����2 */
#define FLMCR2 (*(volatile unsigned char *)0xffff41)
/* �õ�֥�å�����쥸����1 */
#define EBR1 (*(volatile unsigned char *)0xffff42)
/* �õ�֥�å�����쥸����2 */
#define EBR2 (*(volatile unsigned char *)0xffff43)
/* RAM����ȥ���쥸���� */
#define RAMCR (*(volatile unsigned char *)0xffff47)

/* ��������Ͼ��ִ�Ϣ */
/* �����ƥॳ��ȥ���쥸���� */
/* #define SYSCR (*(volatile unsigned char *)0xfffff1 */
/* �⥸�塼�륹����Х�����ȥ���쥸���� */
#define MSTCR (*(volatile unsigned char *)0xffff5e)

/* ����å�ȯ�����Ϣ */
/* ʬ����(CPU����å��դ��������뤿���ʬ����) */
/* ʬ���楳��ȥ���쥸���� */
#define DIVCR (*(volatile unsigned char *)0xffff5d)

/* IRQ��Ϣ */
/* IRQ���󥹥���ȥ���쥸���� */
#define ISCR (*(volatile unsigned char *)0xfffff4)
/* IRQ���͡��֥�쥸���� */
#define IER (*(volatile unsigned char *)0xfffff5)
/* IRQ���ơ������쥸���� */
#define ISR (*(volatile unsigned char *)0xfffff6)
/* ���󥿥�ץȡ��ץ饤����ƥ��쥸����A */
#define IPRA (*(volatile unsigned char *)0xfffff8)
/* ���󥿥�ץȡ��ץ饤����ƥ��쥸����B */
#define IPRB (*(volatile unsigned char *)0xfffff9)

/* �Х�����ȥ����Ϣ */
/* �Х�������ȥ���쥸���� */
#define ABWCR (*(volatile unsigned char *)0xffffec)
/* �����������ơ��ȥ���ȥ���쥸���� */
#define ASTCR (*(volatile unsigned char *)0xffffed)
/* �������ȥ���ȥ���쥸���� */
#define WCR (*(volatile unsigned char *)0xffffee)
/* �������ȥ��ơ��ȥ���ȥ��饤�͡��֥�쥸���� */
#define WCER (*(volatile unsigned char *)0xffffef)
/* �Х���꡼������ȥ���쥸���� */
#define BRCR (*(volatile unsigned char *)0xfffff3)
/* ���åץ��쥯�ȥ���ȥ���쥸���� */
#define CSCR (*(volatile unsigned char *)0xffff5f)

/* ��ե�å��女��ȥ���(D-RAM����) */
/* ��ե�å��女��ȥ���쥸���� */
#define RFSHCR (*(volatile unsigned char *)0xffffac)
/* ��ե�å��奿���ޥ���ȥ��롦���ơ������쥸���� */
#define RTMCSR (*(volatile unsigned char *)0xffffad)
/* ��ե�å��奿���ޥ����� */
#define RTCNT (*(volatile unsigned char *)0xffffae)
/* ��ե�å��奿���ॳ�󥹥���ȥ쥸���� */
#define RTCOR (*(volatile unsigned char *)0xffffaf)

/* DMA����ȥ����Ϣ */
/* ����ͥ� 0A */
/* ���ꥢ�ɥ쥹�쥸����0AR */
#define MAR0AR (*(volatile unsigned char *)0xffff20)
/* ���ꥢ�ɥ쥹�쥸����0AE */
#define MAR0AE (*(volatile unsigned char *)0xffff21)
/* ���ꥢ�ɥ쥹�쥸����0AH */
#define MAR0AH (*(volatile unsigned char *)0xffff22)
/* ���ꥢ�ɥ쥹�쥸����0AL */
#define MAR0AL (*(volatile unsigned char *)0xffff23)
/* ž��������ȥ쥸����0AH */
#define ETCR0AH (*(volatile unsigned char *)0xffff24)
/* ž��������ȥ쥸����0AL */
#define ETCR0AL (*(volatile unsigned char *)0xffff25)
/* I/O���ɥ쥹�쥸����0A */
#define IOAR0A (*(volatile unsigned char *)0xffff26)
/* �ǡ���ž������쥸����0A */
#define DTCR0A (*(volatile unsigned char *)0xffff27)
/* ����ͥ� 0B */
/* ���ꥢ�ɥ쥹�쥸����0BR */
#define MAR0BR (*(volatile unsigned char *)0xffff28)
/* ���ꥢ�ɥ쥹�쥸����0BE */
#define MAR0BE (*(volatile unsigned char *)0xffff29)
/* ���ꥢ�ɥ쥹�쥸����0BH */
#define MAR0BH (*(volatile unsigned char *)0xffff2a)
/* ���ꥢ�ɥ쥹�쥸����0BL */
#define MAR0BL (*(volatile unsigned char *)0xffff2b)
/* ž��������ȥ쥸����0BH */
#define ETCR0BH (*(volatile unsigned char *)0xffff2c)
/* ž��������ȥ쥸����0BL */
#define ETCR0BL (*(volatile unsigned char *)0xffff2d)
/* I/O���ɥ쥹�쥸����0B */
#define IOAR0B (*(volatile unsigned char *)0xffff2e)
/* �ǡ���ž������쥸����0B */
#define DTCR0B (*(volatile unsigned char *)0xffff2f)
/* ����ͥ� 1A */
/* ���ꥢ�ɥ쥹�쥸����1AR */
#define MAR1AR (*(volatile unsigned char *)0xffff30)
/* ���ꥢ�ɥ쥹�쥸����1AE */
#define MAR1AE (*(volatile unsigned char *)0xffff31)
/* ���ꥢ�ɥ쥹�쥸����1AH */
#define MAR1AH (*(volatile unsigned char *)0xffff32)
/* ���ꥢ�ɥ쥹�쥸����1AL */
#define MAR1AL (*(volatile unsigned char *)0xffff33)
/* ž��������ȥ쥸����1AH */
#define ETCR1AH (*(volatile unsigned char *)0xffff34)
/* ž��������ȥ쥸����1AL */
#define ETCR1AL (*(volatile unsigned char *)0xffff35)
/* I/O���ɥ쥹�쥸����1A */
#define IOAR1A (*(volatile unsigned char *)0xffff36)
/* �ǡ���ž������쥸����1A */
#define DTCR1A (*(volatile unsigned char *)0xffff37)
/* ����ͥ� 1B */
/* ���ꥢ�ɥ쥹�쥸����1BR */
#define MAR1BR (*(volatile unsigned char *)0xffff38)
/* ���ꥢ�ɥ쥹�쥸����1BE */
#define MAR1BE (*(volatile unsigned char *)0xffff39)
/* ���ꥢ�ɥ쥹�쥸����1BH */
#define MAR1BH (*(volatile unsigned char *)0xffff3a)
/* ���ꥢ�ɥ쥹�쥸����1BL */
#define MAR1BL (*(volatile unsigned char *)0xffff3b)
/* ž��������ȥ쥸����1BH */
#define ETCR1BH (*(volatile unsigned char *)0xffff3c)
/* ž��������ȥ쥸����1BL */
#define ETCR1BL (*(volatile unsigned char *)0xffff3d)
/* I/O���ɥ쥹�쥸����1B */
#define IOAR1B (*(volatile unsigned char *)0xffff3e)
/* �ǡ���ž������쥸����1B */
#define DTCR1B (*(volatile unsigned char *)0xffff3f)

/* IO�ݡ��ȴ�Ϣ */
/* �ݡ��ȣ��ǡ����ǥ��쥯�����쥸���� */
#define P1DDR (*(volatile unsigned char *)0xffffc0)
/* �ݡ��ȣ��ǡ����쥸���� */
#define P1DR (*(volatile unsigned char *)0xffffc2)
/* �ݡ��ȣ��ǡ����ǥ��쥯�����쥸���� */
#define P2DDR (*(volatile unsigned char *)0xffffc1)
/* �ݡ��ȣ��ǡ����쥸���� */
#define P2DR (*(volatile unsigned char *)0xffffc3)
/* �ݡ��ȣ����ϥץ륢�å�MOS����ȥ���쥸���� */
#define P2PCR (*(volatile unsigned char *)0xffffd8)
/* �ݡ��ȣ��ǡ����ǥ��쥯�����쥸���� */
#define P3DDR (*(volatile unsigned char *)0xffffc4)
/* �ݡ��ȣ��ǡ����쥸���� */
#define P3DR (*(volatile unsigned char *)0xffffc6)
/* �ݡ��ȣ��ǡ����ǥ��쥯�����쥸���� */
#define P4DDR (*(volatile unsigned char *)0xffffc5)
/* �ݡ��ȣ��ǡ����쥸���� */
#define P4DR (*(volatile unsigned char *)0xffffc7)
/* �ݡ��ȣ����ϥץ륢�å�MOS����ȥ���쥸���� */
#define P4PCR (*(volatile unsigned char *)0xffffda)
/* �ݡ��ȣ��ǡ����ǥ��쥯�����쥸���� */
#define P5DDR (*(volatile unsigned char *)0xffffc8)
/* �ݡ��ȣ��ǡ����쥸���� */
#define P5DR (*(volatile unsigned char *)0xffffca)
/* �ݡ��ȣ����ϥץ륢�å�MOS����ȥ���쥸���� */
#define P5PCR (*(volatile unsigned char *)0xffffdb)
/* �ݡ��ȣ��ǡ����ǥ��쥯�����쥸���� */
#define P6DDR (*(volatile unsigned char *)0xffffc9)
/* �ݡ��ȣ��ǡ����쥸���� */
#define P6DR (*(volatile unsigned char *)0xffffcb)
/* �ݡ��ȣ��ǡ����쥸���������ϤΤߡ� */
#define P7DR (*(volatile unsigned char *)0xffffce)
/* �ݡ��ȣ��ǡ����ǥ��쥯�����쥸���� */
#define P8DDR (*(volatile unsigned char *)0xffffcd)
/* �ݡ��ȣ��ǡ����쥸�����ʣ��ӥåȡ� */
#define P8DR (*(volatile unsigned char *)0xffffcf)
/* �ݡ��ȣ��ǡ����ǥ��쥯�����쥸���� */
#define P9DDR (*(volatile unsigned char *)0xffffd0)
/* �ݡ��ȣ��ǡ����쥸�����ʣ��ӥåȡ� */
#define P9DR (*(volatile unsigned char *)0xffffd2)
/* �ݡ���A�ǡ����ǥ��쥯�����쥸���� */
#define PADDR (*(volatile unsigned char *)0xffffd1)
/* �ݡ���A�ǡ����쥸���� */
#define PADR (*(volatile unsigned char *)0xffffd3)
/* �ݡ���B�ǡ����ǥ��쥯�����쥸���� */
#define PBDDR (*(volatile unsigned char *)0xffffd4)
/* �ݡ���B�ǡ����쥸���� */
#define PBDR (*(volatile unsigned char *)0xffffd6)

/* ITU (16�ӥåȥ�����) */
/* ����ͥ붦�� */
/* �����ޥ������ȥ쥸���� */
#define TSTR (*(volatile unsigned char *)0xffff60)
/* �����ޥ��󥯥�쥸���� */
#define TSNC (*(volatile unsigned char *)0xffff61)
/* �����ޥ⡼�ɥ쥸���� */
#define TMDR (*(volatile unsigned char *)0xffff62)
/* �����ޥե��󥯥���󥳥�ȥ���쥸���� */
#define TFCR (*(volatile unsigned char *)0xffff63)
/* �����ޥ����ȥץåȥޥ������͡��֥�쥸���� */
#define TOER (*(volatile unsigned char *)0xffff90)
/* �����ޥ����ȥץåȥ���ȥ���쥸���� */
#define TOCR (*(volatile unsigned char *)0xffff91)
/* ����ͥ�0 */
/* �����ޥ���ȥ���쥸����0 */
#define TCR0 (*(volatile unsigned char *)0xffff64)
/* ������I/O����ȥ���쥸����0 */
#define TIOR0 (*(volatile unsigned char *)0xffff65)
/* �����ޥ��󥿥�ץȥ��͡��֥�쥸����0 */
#define TIER0 (*(volatile unsigned char *)0xffff66)
/* �����ޥ��ơ������쥸����0 */
#define TSR0 (*(volatile unsigned char *)0xffff67)
/* �����ޥ�����0H */
#define TCNT0H (*(volatile unsigned char *)0xffff68)
/* �����ޥ�����0L */
#define TCNT0L (*(volatile unsigned char *)0xffff69)
/* �����ͥ��쥸����A0H */
#define GRA0H (*(volatile unsigned char *)0xffff6a)
/* �����ͥ��쥸����A0L */
#define GRA0L (*(volatile unsigned char *)0xffff6b)
/* �����ͥ��쥸����B0H */
#define GRB0H (*(volatile unsigned char *)0xffff6c)
/* �����ͥ��쥸����B0L */
#define GRB0L (*(volatile unsigned char *)0xffff6d)
/* ����ͥ�1 */
/* �����ޥ���ȥ���쥸����1 */
#define TCR1 (*(volatile unsigned char *)0xffff6e)
/* ������I/O����ȥ���쥸������ */
#define TIOR1 (*(volatile unsigned char *)0xffff6f)
/* �����ޥ��󥿥�ץȥ��͡��֥�쥸����1 */
#define TIER1 (*(volatile unsigned char *)0xffff70)
/* �����ޥ��ơ������쥸����1 */
#define TSR1 (*(volatile unsigned char *)0xffff71)
/* �����ޥ����󥿣�H */
#define TCNT1H (*(volatile unsigned char *)0xffff72)
/* �����ޥ����󥿣�L */
#define TCNT1L (*(volatile unsigned char *)0xffff73)
/* �����ͥ��쥸����A1H */
#define GRA1H (*(volatile unsigned char *)0xffff74)
/* �����ͥ��쥸����A1L */
#define GRA1L (*(volatile unsigned char *)0xffff75)
/* �����ͥ��쥸����B1H */
#define GRB1H (*(volatile unsigned char *)0xffff76)
/* �����ͥ��쥸����B1L */
#define GRB1L (*(volatile unsigned char *)0xffff77)
/* ����ͥ�2 */
/* �����ޥ���ȥ���쥸����2 */
#define TCR2 (*(volatile unsigned char *)0xffff78)
/* ������I/O����ȥ���쥸����2 */
#define TIOR2 (*(volatile unsigned char *)0xffff79)
/* �����ޥ��󥿥�ץȥ��͡��֥�쥸����2 */
#define TIER2 (*(volatile unsigned char *)0xffff7a)
/* �����ޥ��ơ������쥸����2 */
#define TSR2 (*(volatile unsigned char *)0xffff7b)
/* �����ޥ�����2H */
#define TCNT2H (*(volatile unsigned char *)0xffff7c)
/* �����ޥ�����2L */
#define TCNT2L (*(volatile unsigned char *)0xffff7d)
/* �����ͥ��쥸����A2H */
#define GRA2H (*(volatile unsigned char *)0xffff7e)
/* �����ͥ��쥸����A2L */
#define GRA2L (*(volatile unsigned char *)0xffff7f)
/* �����ͥ��쥸����B2H */
#define GRB2H (*(volatile unsigned char *)0xffff80)
/* �����ͥ��쥸����B2L */
#define GRB2L (*(volatile unsigned char *)0xffff81)
/* ����ͥ�3 */
/* �����ޥ���ȥ���쥸����3 */
#define TCR3 (*(volatile unsigned char *)0xffff82)
/* ������I/O����ȥ���쥸����3 */
#define TIOR3 (*(volatile unsigned char *)0xffff83)
/* �����ޥ��󥿥�ץȥ��͡��֥�쥸����3 */
#define TIER3 (*(volatile unsigned char *)0xffff84)
/* �����ޥ��ơ������쥸����3 */
#define TSR3 (*(volatile unsigned char *)0xffff85)
/* �����ޥ�����3H */
#define TCNT3H (*(volatile unsigned char *)0xffff86)
/* �����ޥ�����3L */
#define TCNT3L (*(volatile unsigned char *)0xffff87)
/* �����ͥ��쥸����A3H */
#define GRA3H (*(volatile unsigned char *)0xffff88)
/* �����ͥ��쥸����A3L */
#define GRA3L (*(volatile unsigned char *)0xffff89)
/* �����ͥ��쥸����B3H */
#define GRB3H (*(volatile unsigned char *)0xffff8a)
/* �����ͥ��쥸����B3L */
#define GRB3L (*(volatile unsigned char *)0xffff8b)
/* �Хåե��쥸����A3H */
#define BRA3H (*(volatile unsigned char *)0xffff8c)
/* �Хåե��쥸����A3L */
#define BRA3L (*(volatile unsigned char *)0xffff8d)
/* �Хåե��쥸����B3H */
#define BRB3H (*(volatile unsigned char *)0xffff8e)
/* �Хåե��쥸����B3L */
#define BRB3L (*(volatile unsigned char *)0xffff8f)
/* ����ͥ�4 */
/* �����ޥ���ȥ���쥸����4 */
#define TCR4 (*(volatile unsigned char *)0xffff92)
/* ������I/O����ȥ���쥸����4 */
#define TIOR4 (*(volatile unsigned char *)0xffff93)
/* �����ޥ��󥿥�ץȥ��͡��֥�쥸����4 */
#define TIER4 (*(volatile unsigned char *)0xffff94)
/* �����ޥ��ơ������쥸����4 */
#define TSR4 (*(volatile unsigned char *)0xffff95)
/* �����ޥ�����4H */
#define TCNT4H (*(volatile unsigned char *)0xffff96)
/* �����ޥ�����4L */
#define TCNT4L (*(volatile unsigned char *)0xffff97)
/* �����ͥ��쥸����A4H */
#define GRA4H (*(volatile unsigned char *)0xffff98)
/* �����ͥ��쥸����A4L */
#define GRA4L (*(volatile unsigned char *)0xffff99)
/* �����ͥ��쥸����B4H */
#define GRB4H (*(volatile unsigned char *)0xffff9a)
/* �����ͥ��쥸����B4L */
#define GRB4L (*(volatile unsigned char *)0xffff9b)
/* �Хåե��쥸����A4H */
#define BRA4H (*(volatile unsigned char *)0xffff9c)
/* �Хåե��쥸����A4L */
#define BRA4L (*(volatile unsigned char *)0xffff9d)
/* �Хåե��쥸����B4H */
#define BRB4H (*(volatile unsigned char *)0xffff9e)
/* �Хåե��쥸����B4L */
#define BRB4L (*(volatile unsigned char *)0xffff9f)

/* �ץ���ޥ֥륿���ߥ󥰥ѥ����󥳥�ȥ����Ϣ */
/* �ݡ���A�ǡ����ǥ��쥯�����쥸���� */
/* #define PADDR (*(volatile unsigned char *)0xffffd1) */
/* �ݡ���A�ǡ����쥸���� */
/* #define PADR (*(volatile unsigned char *)0xffffd3) */
/* �ݡ���B�ǡ����ǥ��쥯�����쥸���� */
/* #define PBDDR (*(volatile unsigned char *)0xffffd4) */
/* �ݡ���B�ǡ����쥸���� */
/* #define PBDR (*(volatile unsigned char *)0xffffd6) */
/* TPC���ϥ⡼�ɥ쥸���� */
#define TPMR (*(volatile unsigned char *)0xffffa0)
/* TPC���ϥ���ȥ���쥸���� */
#define TPCR (*(volatile unsigned char *)0xffffa1)
/* �ͥ����ȥǡ������͡��֥�쥸����B */
#define NDERB (*(volatile unsigned char *)0xffffa2)
/* �ͥ����ȥǡ������͡��֥�쥸����A */
#define NDERA (*(volatile unsigned char *)0xffffa3)
/* �ͥ����ȥǡ����쥸����A(���ϥȥꥬ��Ʊ��ΤȤ�) */
#define NDRA (*(volatile unsigned char *)0xffffa5)
/* �ͥ����ȥǡ����쥸����A1(���ϥȥꥬ���ۤʤ�Ȥ����롼��1) */
#define NDRA1 (*(volatile unsigned char *)0xffffa5)
/* �ͥ����ȥǡ����쥸����A0(���ϥȥꥬ���ۤʤ�Ȥ����롼��0) */
#define NDRA0 (*(volatile unsigned char *)0xffffa7)
/* �ͥ����ȥǡ����쥸����B(���ϥȥꥬ��Ʊ��ΤȤ�) */
#define NDRB (*(volatile unsigned char *)0xffffa4)
/* �ͥ����ȥǡ����쥸����B1(���ϥȥꥬ���ۤʤ�Ȥ����롼��3) */
#define NDRB3 (*(volatile unsigned char *)0xffffa4)
/* �ͥ����ȥǡ����쥸����B0(���ϥȥꥬ���ۤʤ�Ȥ����롼��2) */
#define NDRB2 (*(volatile unsigned char *)0xffffa6)

/* �����å��ɥå�������(WDT)��Ϣ */
/* �����ޥ���ȥ���/���ơ������쥸���� */
#define TCSR (*(volatile unsigned char *)0xffffa8)
/* �����ޥ����� */
#define TCNT (*(volatile unsigned char *)0xffffa9)
/* �ꥻ�åȥ���ȥ���/���ơ������쥸���� */
#define RSTCSR (*(volatile unsigned char *)0xffffab)

/* ���ꥢ�륳�ߥ�˥�������󥤥󥿡��ե�����(SCI) */
/* �ڤ� ���ޡ��ȥ����ɥ��󥿡��ե�������Ϣ */
/* ����ͥ�0 (USB�Ѵ�����³����ͥ�) */
/* ���ꥢ��⡼�ɥ쥸���� */
#define SMR0 (*(volatile unsigned char *)0xffffb0)
/* �ӥåȥ졼�ȥ쥸���� */
#define BRR0 (*(volatile unsigned char *)0xffffb1)
/* ���ꥢ�륳��ȥ���쥸���� */
#define SCR0 (*(volatile unsigned char *)0xffffb2)
/* �ȥ�󥹥ߥåȥǡ����쥸���� */
#define TDR0 (*(volatile unsigned char *)0xffffb3)
/* ���ꥢ�륹�ơ������쥸���� */
#define SSR0 (*(volatile unsigned char *)0xffffb4)
/* �쥷���֥ǡ����쥸���� */
#define RDR0 (*(volatile unsigned char *)0xffffb5)
/* ���ޡ��ȥ����ɥ⡼�ɥ쥸���� */
#define SCMR (*(volatile unsigned char *)0xffffb6)
/* ����ͥ�1 (ROM�񤭹��ߥ���ͥ�)*/
/* ���ꥢ��⡼�ɥ쥸���� */
#define SMR1 (*(volatile unsigned char *)0xffffb8)
/* �ӥåȥ졼�ȥ쥸���� */
#define BRR1 (*(volatile unsigned char *)0xffffb9)
/* ���ꥢ�륳��ȥ���쥸���� */
#define SCR1 (*(volatile unsigned char *)0xffffba)
/* �ȥ�󥹥ߥåȥǡ����쥸���� */
#define TDR1 (*(volatile unsigned char *)0xffffbb)
/* ���ꥢ�륹�ơ������쥸���� */
#define SSR1 (*(volatile unsigned char *)0xffffbc)
/* �쥷���֥ǡ����쥸���� */
#define RDR1 (*(volatile unsigned char *)0xffffbd)

/* A/D�Ѵ����Ϣ */
/* A/D�ǡ����쥸����AH */
#define ADDRAH (*(volatile unsigned char *)0xffffe0)
/* A/D�ǡ����쥸����AL */
#define ADDRAL (*(volatile unsigned char *)0xffffe1)
/* A/D�ǡ����쥸����BH */
#define ADDRBH (*(volatile unsigned char *)0xffffe2)
/* A/D�ǡ����쥸����BL */
#define ADDRBL (*(volatile unsigned char *)0xffffe3)
/* A/D�ǡ����쥸����CH */
#define ADDRCH (*(volatile unsigned char *)0xffffe4)
/* A/D�ǡ����쥸����CL */
#define ADDRCL (*(volatile unsigned char *)0xffffe5)
/* A/D�ǡ����쥸����DH */
#define ADDRDH (*(volatile unsigned char *)0xffffe6)
/* A/D�ǡ����쥸����DL */
#define ADDRDL (*(volatile unsigned char *)0xffffe7)
/* A/D����ȥ���/���ơ������쥸���� */
#define ADCSR (*(volatile unsigned char *)0xffffe8)
/* A/D����ȥ���쥸���� */
#define ADCR (*(volatile unsigned char *)0xffffe9)

/* D/A�Ѵ����Ϣ */
/* D/A�ǡ����쥸����0 */
#define DADR0 (*(volatile unsigned char *)0xffffdc)
/* D/A�ǡ����쥸����1 */
#define DADR1 (*(volatile unsigned char *)0xffffdd)
/* D/A����ȥ���쥸���� */
#define DACR (*(volatile unsigned char *)0xffffde)
/* D/A������Х�����ȥ���쥸���� */
#define DASTCR (*(volatile unsigned char *)0xffff5c)
