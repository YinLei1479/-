MIL_3_Tfile_Hdr_ 145A 140A modeler 9 66965547 66A36377 25 ray-laptop 28918 0 0 none none 0 0 none 65D95EE2 2CE3 0 0 0 0 0 0 1bcc 1                                                                                                                                                                                                                                                                                                                                                                                              ��g�      @   D   H      �  *�  *�  *�  *�  *�  *�  *�  �           	   begsim intrpt         
   ����   
   doc file            	nd_module      endsim intrpt             ����      failure intrpts            disabled      intrpt interval         ԲI�%��}����      priority              ����      recovery intrpts            disabled      subqueue                     count    ���   
   ����   
      list   	���   
          
      super priority             ����             /* my node address */   int	\my_address;       Objid	\my_id;       Objid	\my_node_id;       /* rcv pk type */   
int	\type;       int	\interactive_id;       '/* the next hop to the interact node */   int	\to_interact_next_hop;       /* the Num of the pk */   int	\interact_pk_num;       /* 0 or 1 for the net topo */   int	\topo[24][24];       #/* pk num of interact collection */   int	\link_interact_pk_num;       /* time out self intrpt */   Evhandle	\evh;          Packet* pkptr;   int source;   int i,j;      #include <math.h>       /* Constant Definitions */   #define RX_IN		(0)   #define SRC_IN		(1)   #define TX_OUT		(0)   #define SINK_OUT	(1)           #define COLLECT_FINISH	(5000)   #define TIME_OUT_SIGNAL (6000)   #define INTACT_PK_SEND	(7000)       "/* Transition Condition Macros */    Z#define FROM_RX_PK			(op_intrpt_type() == OPC_INTRPT_STRM) && (op_intrpt_strm () == RX_IN)   \#define FROM_SRC_PK 		(op_intrpt_type() == OPC_INTRPT_STRM) && (op_intrpt_strm () == SRC_IN)       e#define INTACT_START 		(op_intrpt_type() == OPC_INTRPT_SELF) && (op_intrpt_code () == INTACT_PK_SEND)   a#define COLLECT				(op_intrpt_type() == OPC_INTRPT_SELF) && (op_intrpt_code () == COLLECT_FINISH)   b#define TIME_OUT			(op_intrpt_type() == OPC_INTRPT_SELF) && (op_intrpt_code () == TIME_OUT_SIGNAL)   .   -/*static void QWZ_rcv(Packet* pkptr)//QWZ_RCV   	{   	int nei_id;   	int nei_slot;   	int nei_in_flag;   	int two_nei_num;   	int two_nei_id[8];   	//int two_nei_in_flag;   	//int count_in;   	int i;   	   	FIN(QWZ_rcv(Packet* pkptr));   +	op_pk_nfd_get (pkptr, "Address", &nei_id);   *	op_pk_nfd_get (pkptr, "Slot", &nei_slot);   	nei_in_flag=0;   +	if(my_neighbor[nei_id][0]==0) nei_count++;   	my_neighbor[nei_id][0]=1;   !	my_neighbor[nei_id][1]=nei_slot;   	//����ھӱ�����ռ��ʱ϶   	   	   0	op_pk_nfd_get (pkptr, "Nei_num", &two_nei_num);   8	op_pk_nfd_get (pkptr, "Nei_address_0", &two_nei_id[0]);   8	op_pk_nfd_get (pkptr, "Nei_address_1", &two_nei_id[1]);   8	op_pk_nfd_get (pkptr, "Nei_address_2", &two_nei_id[2]);   8	op_pk_nfd_get (pkptr, "Nei_address_3", &two_nei_id[3]);   8	op_pk_nfd_get (pkptr, "Nei_address_4", &two_nei_id[4]);   8	op_pk_nfd_get (pkptr, "Nei_address_5", &two_nei_id[5]);   8	op_pk_nfd_get (pkptr, "Nei_address_6", &two_nei_id[6]);   8	op_pk_nfd_get (pkptr, "Nei_address_7", &two_nei_id[7]);   	for(i=0;i<two_nei_num;i++)   		{   :		if(my_two_nei[two_nei_id[i]]==0) my_two_nei_count_sum++;   		my_two_nei[two_nei_id[i]]=1;   		}   	//��������ھӽڵ��ռ�   	   	now_slot_id[nei_id]=1;   4	now_slot_QWZ_num++;//�ռ���֡��QWZ��Ŀ�뷢��QWZ��ַ   	   	FOUT;   	}   	*/   	   	   		                                          Z   �          
   init   
       
   !   //initial begin   my_id = op_id_self();   $my_node_id = op_topo_parent (my_id);       6op_ima_obj_attr_get(my_node_id,"Address",&my_address);       interactive_id=0xFF;   to_interact_next_hop=0xFF;   interact_pk_num=0;   link_interact_pk_num=0;       for(i=0;i<24;i++)    	for(j=0;j<24;j++) topo[i][j]=0;       :op_intrpt_schedule_self(op_sim_time()+200,INTACT_PK_SEND);   .printf("$$$$$$$$$$$$net over$$$$$$$$$$$$$\n");       $//************for test**************   interactive_id=10;   )if(my_address==0) to_interact_next_hop=1;   *if(my_address==1) to_interact_next_hop=11;   *if(my_address==2) to_interact_next_hop=10;   )if(my_address==3) to_interact_next_hop=4;   *if(my_address==4) to_interact_next_hop=10;   *if(my_address==5) to_interact_next_hop=10;   )if(my_address==6) to_interact_next_hop=5;   *if(my_address==7) to_interact_next_hop=11;   )if(my_address==8) to_interact_next_hop=5;   )if(my_address==9) to_interact_next_hop=2;   +if(my_address==10) to_interact_next_hop=10;   +if(my_address==11) to_interact_next_hop=10;   *if(my_address==12) to_interact_next_hop=4;       
                     
   ����   
          pr_state           �          
   idle   
                                       ����             pr_state        J   Z          
   rx_rcv   
       J   2   	int dest;   int pk_interact_num;   int nei_num;   int nei_id[8];           //�յ���ͬ���Ͱ�����Ϊ   "pkptr=op_pk_get(op_intrpt_strm());   %op_pk_nfd_get (pkptr, "TYPE", &type);       #if(type==6)//�򽻻��ڵ㷢�͵��ϱ�֡   	{   0	op_pk_nfd_get (pkptr, "Num", &pk_interact_num);   &	op_pk_nfd_get (pkptr, "DEST", &dest);   Q	if(dest==my_address && interact_pk_num != pk_interact_num) op_pk_destroy(pkptr);   X	else if(dest!=my_address && interact_pk_num-1 != pk_interact_num) op_pk_destroy(pkptr);   	else   		{   		if(dest!=my_address)   			{   ;			op_pk_nfd_set (pkptr, "Next_Hop", to_interact_next_hop);   			op_pk_send(pkptr,TX_OUT);   			}   		else/////���ǽ����ڵ�   			{   			link_interact_pk_num++;   +			op_pk_nfd_get (pkptr, "Source",&source);   -			op_pk_nfd_get (pkptr, "Nei_num",&nei_num);   6			op_pk_nfd_get (pkptr, "Nei_address_0", &nei_id[0]);   6			op_pk_nfd_get (pkptr, "Nei_address_1", &nei_id[1]);   6			op_pk_nfd_get (pkptr, "Nei_address_2", &nei_id[2]);   6			op_pk_nfd_get (pkptr, "Nei_address_3", &nei_id[3]);   6			op_pk_nfd_get (pkptr, "Nei_address_4", &nei_id[4]);   6			op_pk_nfd_get (pkptr, "Nei_address_5", &nei_id[5]);   6			op_pk_nfd_get (pkptr, "Nei_address_6", &nei_id[6]);   6			op_pk_nfd_get (pkptr, "Nei_address_7", &nei_id[7]);   (			printf("�����ڵ��յ�pk:%d\n",source);   			for(i=0;i<nei_num;i++)   -				topo[source][nei_id[i]]=1;///����topo����   			   O			if(link_interact_pk_num==12)//collect finish!!!!!!!!!!!!!!!!(need to chang!)   				{   				printf("�ռ���ϣ�����\n");   				op_ev_cancel(evh);   :				op_intrpt_schedule_self(op_sim_time(),COLLECT_FINISH);   				}   			//��ýڵ�λ�ò���¼   			}   		}	   	}   J                     
   ����   
          pr_state        �            
   src_rcv   
       
   &   /*   pkptr =  op_pk_get (SRC_IN);   %op_pk_nfd_get (pkptr, "TYPE", &type);       if(type==0)//QWZ   	{   -	op_pk_nfd_set (pkptr, "Nei_num", nei_count);   (	op_pk_nfd_set (pkptr, "Slot", my_slot);   	t_c=0;   	for(i=0;i<24;i++) nei[i]=0xFF;   	for(i=0;i<24;i++)   		{   		if(my_neighbor[i][0]==1)   			{   			nei[t_c]=i;   				t_c++;   			}   		}   0	op_pk_nfd_set (pkptr, "Nei_address_0", nei[0]);   0	op_pk_nfd_set (pkptr, "Nei_address_1", nei[1]);   0	op_pk_nfd_set (pkptr, "Nei_address_2", nei[2]);   0	op_pk_nfd_set (pkptr, "Nei_address_3", nei[3]);   0	op_pk_nfd_set (pkptr, "Nei_address_4", nei[4]);   0	op_pk_nfd_set (pkptr, "Nei_address_5", nei[5]);   0	op_pk_nfd_set (pkptr, "Nei_address_6", nei[6]);   6	op_pk_nfd_set (pkptr, "Nei_address_7", nei[7]);//װ��   	   '	op_pk_send(pkptr,TX_OUT);//send to mac   	   )	printf("%d	QWZ pk send to mac\n",my_id);   	   	for(i=0;i<24;i++)   *		for(j=0;j<2;j++) my_neighbor[i][j]=0xFF;   	nei_count=0;   	my_two_nei_count_sum=0;   4	for(i=0;i<24;i++) my_two_nei[i]=0xFF;//һ֡���һ��   	}   */   
                     
   ����   
          pr_state         �  J          
   interact   
       
      "printf("��������%d\n",my_address);   "printf("time:%f\n",op_sim_time());    if(interactive_id != my_address)   	{   '	pkptr=op_pk_create_fmt("link_report");   (	op_pk_nfd_set(pkptr,"SEND",my_address);   	op_pk_nfd_set(pkptr,"TYPE",6);   *	op_pk_nfd_set(pkptr,"Source",my_address);   ,	op_pk_nfd_set(pkptr,"DEST",interactive_id);   6	op_pk_nfd_set(pkptr,"Next_Hop",to_interact_next_hop);   ,	op_pk_nfd_set(pkptr,"Num",interact_pk_num);   	   	op_pk_send(pkptr,TX_OUT);   *	printf("���ǽ����ڵ㣬����pk����tdma\n");   	   	interact_pk_num+=1;   0	if(interact_pk_num==16) interact_pk_num=0;//Num   	}        if(interactive_id == my_address)   	{   @	evh=op_intrpt_schedule_self(op_sim_time()+180,TIME_OUT_SIGNAL);   $	printf("�ǽ����ڵ㣬������ʱ��\n");   	}   :op_intrpt_schedule_self(op_sim_time()+200,INTACT_PK_SEND);   
                     
   ����   
          pr_state        �   �          
   link_state_feedback   
       
      //packup   %printf("ready to pk up to ground\n");   "printf("time:%f\n",op_sim_time());   3for(i=0;i<13;i++)///////////////////////test for 13   	{   	for(j=0;j<13;j++)   		printf("%d   ",topo[i][j]);   	printf("\n");   	}           //ready for next circle   interact_pk_num+=1;   /if(interact_pk_num==16) interact_pk_num=0;//Num       &link_interact_pk_num=0;//pk collection       for(i=0;i<24;i++)   &	for(j=0;j<24;j++) topo[i][j]=0;//topo   
                     
   ����   
          pr_state          
              �   �      g   �   �   �          
   tr_0   
       ����          ����          
    ����   
          ����                       pr_transition               �   �         �   �   �   �   �     �          
   tr_1   
       
   default   
       ����          
    ����   
          ����                       pr_transition              '   �        �  9   h          
   tr_3   
       
   
FROM_RX_PK   
       ����          
    ����   
          ����                       pr_transition              5   �     H   j     �          
   tr_5   
       ����          ����          
    ����   
          ����                       pr_transition                 �        �  �   �          
   tr_6   
       
   FROM_SRC_PK   
       ����          
    ����   
          ����                       pr_transition              x   �     �       �          
   tr_7   
       
����   
       ����          
    ����   
          ����                       pr_transition               �  
         �   �  :          
   tr_8   
       
   INTACT_START   
       ����          
    ����   
          ����                       pr_transition      	         �        �  3     �          
   tr_9   
       ����          ����          
    ����   
          ����                       pr_transition      
        p   �        �  �   �          
   tr_10   
       
   COLLECT || TIME_OUT   
       ����          
    ����   
          ����                       pr_transition              n   �     �   �  &   �          
   tr_11   
       ����          ����          
    ����   
          ����                       pr_transition                                             