extern int timer_set(int ch, unsigned int time_us);
     /* �������ͥ�Υ����ޤ������ֳִ֤ǳ���������     */
     /* ch:0-4, time_us:1-20971 ���ϰϤǤʤ�������ư��ʤ� */
     /* ch = x (x = 0-4) �ΤȤ� int_imiax() �����椬�ܤ�     */
     /* CPU���Τγ����ߵ��Ĥ�Ф��ʤ����ư���ʤ�          */
     /* �����: ���꤬Ŭ���ʤȤ���1��Ŭ���Ǥʤ��Ȥ��� -1     */
extern void timer_start(int ch);
     /* �������ͥ�Υ�����ư��� */
     /* ch: 0-4 */
extern void timer_stop(int ch);
     /* �������ͥ�Υ�����ư����� */
     /* ch: 0-4 */
extern void timer_init(void);
     /* 16�ӥåȥ����ޤν���� */
extern void timer_intflag_reset(int ch);
     /* �������ͥ�Υ����ޤγ����ߥե饰�Υꥻ�åȤ�Ԥ��ؿ�   */
     /* �������ͥ���ϰ� ch: 0-4                                 */
     /* �����ߥϥ�ɥ���γ����ߤ���Ĥ�������ɬ���ƤӽФ����� */

