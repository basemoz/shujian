
void copy_menpai3()
{
	switch(u_menpai)
	{
	case "mj":												//�趨�����书
			set("family/family_name","����");
			set_skill("piaoyi-shenfa",500);						//�����Ṧ��Ʈ����
			map_skill("dodge", "piaoyi-shenfa");
			set_skill("qiankun-danuoyi",500);
			u_f_pfm=u_f_pfm + ({(: perform_action, "parry.hua" :)});	
			u_f_pfm=u_f_pfm + ({(: perform_action, "parry.xu" :)});	
			//u_f_pfm=u_f_pfm + ({(: perform_action, "parry.yin" :)});
			switch(in_level)
			{
				case 0:
					set_skill("shenghuo-shengong",500);									//���̵ͼ��ڹ���ʥ����
					map_skill("force","shenghuo-shengong");

					switch(random(2))
					{
						case 0:
							set_skill("yingzhua-shou",500);                             //���̵ͼ����֣�ӥצ������
							map_skill("hand","yingzhua-shou");
							nw_parry="qiankun-danuoyi";									//�趨Ǭ����Ų��Ϊ�м�
							prepare_skill("hand", "yingzhua-shou");
							set("f_skill","yingzhua-shou");
						break;
						case 1:
							set_skill("hanbing-mianzhang",500);                             //���̵ͼ����֣���������
							map_skill("strike","hanbing-mianzhang");
							nw_parry="hanbing-mianzhang";									//pfm xixue Ҫ��parry Ϊhanbing-mianzhang
							prepare_skill("strike", "hanbing-mianzhang");
							u_pfm = u_pfm + ({(: perform_action, "strike.xixue" :)});		//��������pfm:��Ѫ
							set("f_skill","hanbing-mianzhang");
						break;

					}
					switch(random(2))
					{
						case 0:
							set_skill("liehuo-jian",500);                             		  //���̵ͼ��������һ�
							map_skill("sword","liehuo-jian");
							w_parry="qiankun-danuoyi";									      //�趨Ǭ����Ų��Ϊ�м�
							u_weapon="sword";
							set("f_w_skill","liehuo-jian");
						break;
						case 1:
							set_skill("lieyan-dao",500);                              		 //���̵ͼ����������浶
							map_skill("blade","lieyan-dao");
							w_parry="qiankun-danuoyi";										 //�趨Ǭ����Ų��Ϊ�м�
							u_w_pfm = u_w_pfm + ({(: perform_action, "blade.shenghuo" :)});		 //���浶pfm:ʥ��
							u_weapon="blade";
							set("f_w_skill","lieyan-dao");
						break;
					}
				break;
				case 1:
					set_skill("jiuyang-shengong",500);									//���̸߼��ڹ���������
					set_skill("shenghuo-shengong",500);									//���̵ͼ��ڹ���ʥ����
					map_skill("force","jiuyang-shengong");
					u_f_pfm=u_f_pfm + ({(: exert_function, "jiuyang" :)});	 //powerup	
					if(!in_weapon)
					switch(random(1))													//����ʥ�������Ϊcuff����ǿ��Ҫ��tisha��Ҫcuff Ϊshenghuo-lingfa �򲻺�
					{																	//���������˿��ֺ����̵������书����ȭ�� campsun ע	
						case 0:
							set_skill("qishang-quan",500);								//���̸߼����֣�����ȭ		
							map_skill("cuff","qishang-quan");
							nw_parry="qiankun-danuoyi";										//�趨Ǭ����Ų��Ϊ�м�
							prepare_skill("cuff","qishang-quan");
							u_pfm = u_pfm + ({(: perform_action, "cuff.qishang" :)});     //����ȭpfm������
							u_pfm = u_pfm + ({(: perform_action, "cuff.duanhun" :)});     //����ȭpfm���ϻ�
							set("f_skill","qishang-quan");
						break;
					}
					else
					switch(random(1))
					{
						case 0:
							set_skill("shenghuo-lingfa",500);										//���̸߼�������ʥ���
							map_skill("dagger","shenghuo-lingfa");									//�趨Ǭ����Ų��Ϊ�м�
							if(in_weapon)
							{
								pmap = query_skill_prepare();
								if (sizeof(pmap))
								{
									skill = keys(pmap);
									foreach (string item in skill)
									prepare_skill(item);
								}																		//��ֹhubei
								
								map_skill("cuff","shenghuo-lingfa");
								prepare_skill("cuff","shenghuo-lingfa");
								nw_parry="qiankun-danuoyi";
								set("f_skill","shenghuo-lingfa");
							}
							w_parry="qiankun-danuoyi";
							u_w_pfm = u_w_pfm + ({(: perform_action, "dagger.duo" :)});        	//ʥ���pfm����
							u_w_pfm = u_w_pfm + ({(: perform_action, "dagger.ji" :)});			//��
							u_w_pfm = u_w_pfm + ({(: perform_action, "dagger.tisha" :)});			//��ɳ	
							u_w_pfm = u_w_pfm + ({(: perform_action, "dagger.xinmo" :)});			//��ħ
							//u_w_pfm = u_w_pfm + ({(: perform_action, "dagger.tougu" :)});
							//u_w_pfm = u_w_pfm + ({(: perform_action, "dagger.yinfeng" :)});
							u_weapon="dagger";
							set("f_w_skill","shenghuo-lingfa");
						break;
					}					
				break;	
				}
			break;//end case mj	

		case "thd":												//�趨�һ����书
			set("family/family_name","�һ���");
			set_skill("bihai-chaosheng",500);					//�һ����ڹ����̺�������			
			set_skill("suibo-zhuliu",500);						//�һ����Ṧ���沨���� 
			set_skill("qimen-bagua",200);
			set("thd/perform",31);
			map_skill("force", "bihai-chaosheng");
			map_skill("dodge", "suibo-zhuliu");
//			u_f_pfm=u_f_pfm + ({(: exert_function, "play" :)});   //�̺�������pfm������
			u_f_pfm=u_f_pfm + ({(: exert_function, "maze" :)});     //����
			u_ub_pfm=u_ub_pfm + ({(: exert_function, "qimen" :)});     //��������
			u_f_pfm=u_f_pfm + ({(: perform_action, "dodge.wuzhuan" :)});			//�沨����pfm:��ת

			switch(in_level)
			{
				case 0:
					switch(random(3))
					{
						case 0:
							set_skill("lanhua-shou",500);                             //�һ����ͼ����֣�������Ѩ��
							map_skill("hand","lanhua-shou");
							nw_parry="lanhua-shou";
							prepare_skill("hand", "lanhua-shou");
							u_pfm=u_pfm + ({(: perform_action, "hand.fuxue" :)});        //������Ѩ��pfm����Ѩ
							set("f_skill","lanhua-shou");
						break;
						case 1:
							set_skill("luoying-zhang",500);                             //�һ����ͼ����֣���Ӣ����
							map_skill("strike","luoying-zhang");
							nw_parry="luoying-zhang";
							prepare_skill("strike", "luoying-zhang");
							u_pfm=u_pfm + ({(: perform_action, "strike.fugu" :)});        //��Ӣ����pfm������
							u_pfm=u_pfm + ({(: perform_action, "strike.pikong" :)});        //��Ӣ����pfm������
							u_pfm=u_pfm + ({(: perform_action, "strike.bading" :)});        //��Ӣ����pfm���ζ�
							set("f_skill","luoying-zhang");

						break;
						case 2:
							set_skill("xuanfeng-tui",500);                             //�һ����ͼ����֣�����ɨҶ��
							set_skill("luoying-zhang",500);                             //pfm xuanfeng ��Ҫ��
							map_skill("strike","luoying-zhang");
							map_skill("leg","xuanfeng-tui");
							nw_parry="xuanfeng-tui";
							prepare_skill("leg", "xuanfeng-tui");
							u_pfm=u_pfm + ({(: perform_action, "leg.kuangfeng" :)});        //����ɨҶ��pfm�����
							set("f_skill","xuanfeng-tui");
						break;
					}
					switch(random(1))															
					{
						case 0:
							set_skill("tanzhi-shentong",500);								//�һ����߼����֣���ָ��ͨ	
							map_skill("finger","tanzhi-shentong");
							map_skill("throwing","tanzhi-shentong");						//��ָ��ͨ������
							w_parry="tanzhi-shentong";
							prepare_skill("finger","tanzhi-shentong");
							u_w_pfm = u_w_pfm + ({(: perform_action, "finger.shentong" :)});     //��ָ��ͨpfm����ͨ
							u_w_pfm = u_w_pfm + ({(: perform_action, "finger.tan" :)});     //��ָ��ͨpfm����
							u_w_pfm = u_w_pfm + ({(: perform_action, "finger.huayu" :)}); 
							switch(random(3))
							{
								case 0:
									set_skill("xuanfeng-tui",500);
									map_skill("leg","xuanfeng-tui");
									set("env/xinghe","xuanfeng-tui");
								break;
								case 1:
									set_skill("lanhua-shou",500);                             
									map_skill("hand","lanhua-shou");
									set("env/xinghe","lanhua-shou");
								break;
								case 2:
									set_skill("luoying-zhang",500); 
									map_skill("strike","luoying-zhang");
									set("env/xinghe","luoying-zhang");
								break;
							
							}
							u_w_pfm = u_w_pfm + ({(: perform_action, "finger.xinghe" :)});     //��ָ��ͨpfm���Ǻ�ǧ����
							set("f_w_skill","tanzhi-shentong");
							u_weapon="feihuangshi";
						break;
					}
																						
				break;
				case 1:
					switch(random(1))
					{
						case 0:
							set_skill("tanzhi-shentong",500);								//�һ����߼����֣���ָ��ͨ	
							map_skill("finger","tanzhi-shentong");
							map_skill("throwing","tanzhi-shentong");						//��ָ��ͨ������
							nw_parry="tanzhi-shentong";
							prepare_skill("finger","tanzhi-shentong");
//							u_pfm = u_pfm + ({(: perform_action, "finger.qiankun" :)});     //��ָ��ͨpfm��Ǭ��һָ
							u_pfm = u_pfm + ({(: perform_action, "finger.tan" :)});     //��ָ��ͨpfm����
							switch(random(3))
							{
								case 0:
									set_skill("xuanfeng-tui",500);
									map_skill("leg","xuanfeng-tui");
									set("env/xinghe","xuanfeng-tui");
								break;
								case 1:
									set_skill("lanhua-shou",500);                             
									map_skill("hand","lanhua-shou");
									set("env/xinghe","lanhua-shou");
								break;
								case 2:
									set_skill("luoying-zhang",500); 
									map_skill("strike","luoying-zhang");
									set("env/xinghe","luoying-zhang");
								break;
							
							}
							u_pfm = u_pfm + ({(: perform_action, "finger.xinghe" :)});     //��ָ��ͨpfm���Ǻ�ǧ����
							set("f_skill","tanzhi-shentong");

						break;
					}
					switch(random(1))
					{
						case 0:
							set_skill("yuxiao-jian",500);										//�һ����߼����������｣��
							set_skill("tanzhi-shentong",500);
							map_skill("finger","tanzhi-shentong");
							set_skill("xuanfeng-tui",500);
							map_skill("leg","xuanfeng-tui");
							set_skill("luoying-zhang",500);
							map_skill("strike","luoying-zhang");
							set_skill("lanhua-shou",500); 
							map_skill("hand","lanhua-shou");
							map_skill("sword","yuxiao-jian");
							w_parry="yuxiao-jian";
							u_w_pfm = u_w_pfm + ({(: perform_action, "sword.feiying" :)});        	//���｣��pfm����Ӱ
							u_w_pfm = u_w_pfm + ({(: perform_action, "sword.qimen" :)});			//����
							u_weapon="xiao";													//pfm feiying ��Ҫװ����Ϊ����		
							set("f_w_skill","yuxiao-jian");
						break;
					}					
				break;	
				}
			break;//end case thd
			
		case "tls":																		//tls kungfu set							
			set("family/family_name","������");
			set("family/master_name","һ�ƴ�ʦ");
			set_skill("qiantian-yiyang",500);											//�����µͼ��ڹ���Ǭ��һ��
			set_skill("tianlong-xiang",500);											//�������Ṧ��������
			set_skill("buddhism",200);
			set("class","bonze");		
			map_skill("force", "qiantian-yiyang");
			map_skill("dodge", "tianlong-xiang");
			u_ub_pfm=u_ub_pfm + ({(: exert_function, "xinjing" :)}); 
			u_ub_pfm=u_ub_pfm + ({(: exert_function, "jujing" :)});  
			switch(in_level)
			{
				case 0:
					switch(random(3))
					{
						case 0:
							set_skill("qingyan-zhang",500);                             		//�����µͼ����֣�����������
							map_skill("strike","qingyan-zhang");
							nw_parry="qingyan-zhang";
							prepare_skill("strike", "qingyan-zhang");
							u_pfm = u_pfm + ({(: perform_action, "strike.piaoying" :)});		//ƮӰ��
							set("f_skill","qingyan-zhang");
						break;
						case 1:
							set_skill("duanjia-quan",500);                             			//�����µͼ����֣��μ�ȭ��
							map_skill("cuff","duanjia-quan");
							nw_parry="duanjia-quan";
							prepare_skill("cuff", "duanjia-quan");
							set("f_skill","duanjia-quan");
						break;
						case 2:
							set_skill("yiyang-zhi",500);										//�����µͼ����֣�һ��ָ
							map_skill("finger","yiyang-zhi");
							nw_parry="yiyang-zhi";
							prepare_skill("finger","yiyang-zhi");
							u_pfm = u_pfm + ({(: perform_action, "finger.sandie" :)}); 			//һ��ָpfm����������
							u_pfm = u_pfm + ({(: perform_action, "finger.yizhisanmai" :)}); 	//һָ����
							u_pfm = u_pfm + ({(: perform_action, "staff.rou" :)});
							set("f_skill","yiyang-zhi");
						break;

					}
					switch(random(1))
					{
						case 0:
							set_skill("duanjia-jianfa",500);                               		//�����µͼ��������μҽ���
							map_skill("sword","duanjia-jianfa");
							if(in_weapon)
							{
								pmap = query_skill_prepare();
								if (sizeof(pmap))
								{
									skill = keys(pmap);
									foreach (string item in skill)
									prepare_skill(item);
								}
								set_skill("qingyan-zhang",500);                             
								map_skill("strike","qingyan-zhang");
								prepare_skill("strike", "qingyan-zhang");
								set("f_skill","qingyan-zhang");
							}
							w_parry="qingyan-zhang";
							u_w_pfm=u_w_pfm + ({(: perform_action, "sword.fenglei" :)});          	//�μҽ���pfm�������Ļ�
							u_weapon="sword";
							set("f_w_skill","duanjia-jianfa");						
						break;
					}
				break;
				case 1:
					set_skill("kurong-changong",500);											//�����¸߼��ڹ�����������
					map_skill("force","kurong-changong");
					switch(random(2))
					{
						case 0:										
							map_skill("strike","kurong-changong");								//�����¸߼����֣���������
							nw_parry="kurong-changong";
							prepare_skill("strike","kurong-changong");
							u_pfm = u_pfm + ({(: exert_function, "rong" :)}); 					//��������pfm����
							u_pfm = u_pfm + ({(: perform_action, "strike.jiuchong" :)});		//������
							u_pfm = u_pfm + ({(: exert_function, "ku" :)});
							set("f_skill","kurong-changong");     
						break;
						case 1:
							u_liumai=str_liumai[random(sizeof(str_liumai))];					//�����¸߼����֣�������
							set("env/liumai",u_liumai);
							set("liumai-shenjian/"+u_liumai,1);
							set_skill("yiyang-zhi",500);
							set_skill("liumai-shenjian",500);										
							map_skill("finger","yiyang-zhi");
							nw_parry="yiyang-zhi";
							prepare_skill("finger","yiyang-zhi");
                                                   u_pfm = u_pfm + ({(: perform_action, "finger.ciqu" :)}); 
							u_pfm = u_pfm + ({(: perform_action, "finger.yizhisanmai" :)});
							u_w_pfm = u_w_pfm + ({(: perform_action, "staff.rou" :)}); 
//							u_pfm = u_pfm + ({(: perform_action, "qianlong" :)});     
							set("f_skill","liumai-shenjian");
						break;
						
					}
					switch(random(3))
					{
						case 0:
							set_skill("cihang-bian",500);										//�����¸߼��������Ⱥ���
							set("shen",530000);												//need for pfm	
							map_skill("whip","cihang-bian");
							w_parry="cihang-bian";
							u_w_pfm = u_w_pfm + ({(: perform_action, "whip.cibei" :)});        		//�Ⱥ���pfm���ȱ��־�
							u_weapon="whip";
							set("f_w_skill","cihang-bian");
						break;
						case 1:
							set_skill("pangen-fu",500);											//�����¸߼��������̸���ḫ
							map_skill("axe","pangen-fu");
							w_parry="pangen-fu";
							u_w_pfm = u_w_pfm + ({(: perform_action, "axe.jingtian" :)});        	//�̸���ḫpfm��������Ƹ�
							u_weapon="axe";
							set("f_w_skill","pangen-fu");
						break;
						case 2:
							map_skill("force", "qiantian-yiyang");
							set_skill("yiyang-zhi",500);											//�����¸߼�������һ��ָ
							map_skill("staff","yiyang-zhi");
							map_skill("finger","yiyang-zhi");
							prepare_skill("finger","yiyang-zhi");
							w_parry="yiyang-zhi";
							u_w_pfm = u_w_pfm + ({(: perform_action, "staff.yin" :)});
							u_weapon="staff";
							set("f_w_skill","yiyang-zhi");						
						
						break;
					}					
				break;	
				}
			break;//end case tls		

		case "sl":		
			set("family/family_name","������");
			set_skill("yijin-jing",500);													//�����ڹ����׽
			set_skill("shaolin-shenfa",500);												//�����Ṧ��������
			set_skill("buddhism",200);														//������������ķ�
			map_skill("force", "yijin-jing");
			map_skill("dodge", "shaolin-shenfa");
			u_f_pfm=u_f_pfm + ({(: exert_function, "jingang" :)});   							//�׽pfm����ղ�������
			switch(in_level)
			{
				case 0:
					switch(random(8))
					{
						case 0:
							set_skill("fengyun-shou",500);                             		//���ֵͼ����֣�������
							map_skill("hand","fengyun-shou");
							nw_parry="fengyun-shou";
							prepare_skill("hand", "fengyun-shou");
							set("f_skill","fengyun-shou");
						break;
						case 1:
							set_skill("yingzhua-gong",500);                             	//���ֵͼ����֣�ӥצ��
							map_skill("claw","yingzhua-gong");
							nw_parry="yingzhua-gong";
							prepare_skill("claw", "yingzhua-gong");
							set("f_skill","yingzhua-gong");
						break;
						case 2:
							set_skill("mohe-zhi",500);                             			//���ֵͼ����֣�Ħڭָ
							map_skill("finger","mohe-zhi");
							nw_parry="mohe-zhi";
							prepare_skill("finger", "mohe-zhi");
							set("f_skill","mohe-zhi");
						break;
						case 3:
							set_skill("jimie-zhua",500);                             		//���ֵͼ����֣�����צ
							map_skill("claw","jimie-zhua");
							nw_parry="jimie-zhua";
							prepare_skill("claw", "jimie-zhua");
							set("f_skill","jimie-zhua");
						break;
						case 4:
							set_skill("shaolin-tantui",500);                             	//���ֵͼ����֣����ֵ���
							map_skill("leg","shaolin-tantui");
							nw_parry="shaolin-tantui";
							prepare_skill("leg", "shaolin-tantui");
							set("f_skill","shaolin-tantui");
						break;
						case 5:
							set_skill("weituo-zhang",500);                             		//���ֵͼ����֣�Τ����
							map_skill("strike","weituo-zhang");
							nw_parry="weituo-zhang";
							prepare_skill("strike", "weituo-zhang");
							set("f_skill","weituo-zhang");
						break;
						case 6:
							set_skill("luohan-quan",500);                             		//���ֵͼ����֣��޺�ȭ
							map_skill("cuff","luohan-quan");
							nw_parry="luohan-quan";
							prepare_skill("cuff", "luohan-quan");
							set("f_skill","luohan-quan");
						break;
						case 7:
							set_skill("sanhua-zhang",500);     								//���ֵͼ����֣�ɢ����
							set_skill("nianhua-zhi",500);                             		//���ֵͼ����֣��黨ָ
                      		map_skill("strike","sanhua-zhang");
    						map_skill("finger","nianhua-zhi");
							prepare_skill("strike", "sanhua-zhang");
							prepare_skill("finger", "nianhua-zhi");
							nw_parry="nianhua-zhi";
							u_pfm = u_pfm + ({(: perform_action, "strike.sanhua" :)});
							u_pfm = u_pfm + ({(: perform_action, "finger.fuxue" :)});    
							set("f_skill","sanhua-zhang");									//ɢ����pfm���ļ�ɢ��
							set("f_skill2","nianhua-zhi");									//�黨ָpfm���黨��Ѩ
							
						break;

					}
					switch(random(8))
					{
						case 0:
							set_skill("xiuluo-dao",500);                               		//���ֵͼ����������޵� 
							map_skill("blade","xiuluo-dao");
							w_parry="xiuluo-dao";
							u_weapon="blade";
							set("f_w_skill","xiuluo-dao");
						break;
						case 1:
							set_skill("pudu-zhang",500);                               		//���ֵͼ��������ն���
							map_skill("staff","pudu-zhang");
							w_parry="pudu-zhang";
							u_weapon="staff";
							set("f_w_skill","pudu-zhang");
						break;
						case 2:
							set_skill("zui-gun",500);                               		//���ֵͼ��������������
							map_skill("club","zui-gun");
							apply_condition("drunk",300);
							w_parry="zui-gun";
							u_weapon="club";
							u_w_pfm = u_w_pfm + ({(: perform_action, "club.zuijiu" :)}); 		//�������pfm���������
							set("f_w_skill","zui-gun");   
						break;
						case 3:
							set_skill("damo-jian",500);                               		//���ֵͼ���������Ħ��
							map_skill("sword","damo-jian");
							w_parry="damo-jian";
							u_weapon="sword";
							set("f_w_skill","damo-jian");
						break;
						case 4:
							set_skill("weituo-gun",500);                               		//���ֵͼ�������Τ�ӹ�
							map_skill("club","weituo-gun");
							w_parry="weituo-gun";
							u_weapon="club";
							set("f_w_skill","weituo-gun");
						break;
						case 5:
							set_skill("cibei-dao",500);                               		//���ֵͼ��������ȱ���
							map_skill("blade","cibei-dao");
							w_parry="cibei-dao";
							u_weapon="blade";
							set("f_w_skill","cibei-dao");
						break;
						case 6:
							set_skill("fumo-jian",500);                               		//���ֵͼ���������ħ��	
							map_skill("sword","fumo-jian");
							w_parry="fumo-jian";
							u_weapon="sword";
							set("f_w_skill","fumo-jian");
						break;
						case 7:
							set_skill("wuchang-zhang",500);                               	//���ֵͼ��������޳���
							map_skill("staff","wuchang-zhang");
							w_parry="wuchang-zhang";
							u_weapon="staff";
							set("f_w_skill","wuchang-zhang");
						break;
					}
				break;
				case 1:
					switch(random(4))
					{
						case 0:
							set_skill("yizhi-chan",500);										//���ָ߼����֣�һָ��
							set_skill("longzhua-gong",500);										//���ָ߼����֣���צ��
							map_skill("claw","longzhua-gong");
							map_skill("finger","yizhi-chan");
							prepare_skill("claw","longzhua-gong");
							prepare_skill("finger","yizhi-chan");
							nw_parry="yizhi-chan";
							u_pfm = u_pfm + ({(: perform_action, "finger.wofo" :)});    		//һָ��pfm������ҷ�
							u_pfm = u_pfm + ({(: perform_action, "finger.qiankun" :)}); 		//һָǬ��
							u_pfm = u_pfm + ({(: perform_action, "claw.canyun" :)}); 			//��צ��pfm��������
							set("f_skill","yizhi-chan");
							set("f_skill2","longzhua-gong");   
   						break;
						case 1:
							set_skill("ruying-suixingtui",500);									//���ָ߼����֣���Ӱ������
							set_skill("qianye-shou",500);										//���ָ߼����֣�����ǧҶ��
							map_skill("leg","ruying-suixingtui");
							map_skill("hand","qianye-shou");
							prepare_skill("leg","ruying-suixingtui");
							prepare_skill("hand","qianye-shou");
							nw_parry="qianye-shou";
							u_pfm = u_pfm + ({(: perform_action, "hand.qianshou" :)});    		//����ǧҶ��pfm��ǧ������
							u_pfm = u_pfm + ({(: perform_action, "leg.ruying" :)});    			//��Ӱ������pfm����Ӱ����
							set("f_skill","ruying-suixingtui");
							set("f_skill2","qianye-shou");
						break;
						case 2:
							set_skill("jingang-quan",500);										//���ָ߼����֣�����ȭ
							map_skill("cuff","jingang-quan");
							set_skill("banruo-zhang",500);										//���ָ߼����֣�������
							map_skill("strike","banruo-zhang");
							nw_parry="banruo-zhang";
							prepare_skill("strike","banruo-zhang");
							prepare_skill("cuff","jingang-quan");
							u_pfm = u_pfm + ({(: perform_action, "strike.chaodu" :)}); 			//������pfm������������
							if(random(5)==1)
							u_pfm = u_pfm + ({(: perform_action, "strike.yipai" :)});   		//һ����ɢ
							u_pfm = u_pfm + ({(: perform_action, "cuff.fumo" :)});    			//����ȭpfm����շ�ħ
							set("f_skill","jingang-quan");
							set("f_skill2","banruo-zhang");
 						break;
 						case 3:
							set_skill("wuxiang-zhi",500);										//���ָ߼����֣������ָ
							map_skill("finger","wuxiang-zhi");
							prepare_skill("finger","wuxiang-zhi");
							nw_parry="wuxiang-zhi";
 							u_pfm = u_pfm + ({(: perform_action, "finger.qiankun" :)}); 		//�����ָpfm������Ǭ��
							set("f_skill","wuxiang-zhi");
   						break;
					}
					switch(random(3))
					{
						case 0:
							set_skill("riyue-bian",500);										//���ָ߼����������±޷�
							map_skill("whip","riyue-bian");
							w_parry="riyue-bian";
							u_w_pfm = u_w_pfm + ({(: perform_action, "whip.fumoquan" :)});        	//���±޷�pfm����շ�ħȦ
							u_w_pfm = u_w_pfm + ({(: perform_action, "whip.chanrao" :)});        	//������� 
							u_weapon="whip";
							set("f_w_skill","riyue-bian");
						break;
						case 1:
							set_skill("ranmu-daofa",500);										//���ָ߼�������ȼľ����
							map_skill("blade","ranmu-daofa");
							w_parry="ranmu-daofa";
//							u_w_pfm = u_w_pfm + ({(: perform_action, "blade.fentian" :)});			//ȼľ����pfm���ٻ����
							u_w_pfm = u_w_pfm + ({(: perform_action, "blade.fenwo" :)});        	//����
							u_w_pfm = u_w_pfm + ({(: perform_action, "blade.fenxin" :)});        	//���� ��Ҫľ�����ܷ�
							u_weapon="blade";
							set("f_w_skill","ranmu-daofa");
						break;
						case 2:
							set_skill("weituo-chu",500);										//���ָ߼�������Τ����
							map_skill("club","weituo-chu");
							w_parry="weituo-chu";
							u_w_pfm = u_w_pfm + ({(: perform_action, "club.leidong" :)});			//Τ����pfm���׶�����
							u_w_pfm = u_w_pfm + ({(: perform_action, "club.chaodu" :)});        	//���ȼ��� 
							u_weapon="club";
							set("f_w_skill","weituo-chu");
						break;
					}					
				break;	
				}
			break;//end case sl	
		case "kl":
			set("family/family_name","������");
			set_skill("xuantian-wuji",500);													//�����ڹ��������޼���
			set_skill("taxue-wuhen",500);													//�����Ṧ��̤ѩ�޺�
			set_skill("art",200);															//������������黭	
			map_skill("force", "xuantian-wuji");
			map_skill("dodge", "taxue-wuhen");
			u_f_pfm=u_f_pfm + ({(: exert_function, "riyue" :)});   							
			u_f_pfm=u_f_pfm + ({(: exert_function, "taxue" :)});     							
			switch(in_level)
			{
				case 0:
					switch(random(2))
					{
						case 0:
							set_skill("chuanyun-tui",500);                            		//���صͼ����֣�������
							map_skill("leg","chuanyun-tui");
							nw_parry="chuanyun-tui";
							prepare_skill("leg", "chuanyun-tui");
							u_pfm = u_pfm + ({(: perform_action, "leg.chuanyun" :)});
							set("f_skill","chuanyun-tui");
						break;
						case 1:
							set_skill("zhentian-quan",500);                            		//���صͼ����֣�����ȭ
							map_skill("cuff","zhentian-quan");
							nw_parry="zhentian-quan";
							prepare_skill("cuff", "zhentian-quan");
							u_pfm = u_pfm + ({(: perform_action, "cuff.kaishan" :)});
							set("f_skill","zhentian-quan");
						break;

					}
					switch(random(1))
					{
						case 0:
							set_skill("xunlei-jian",500);                              		//���صͼ�������Ѹ�׽�
							map_skill("sword","xunlei-jian");
							w_parry="xunlei-jian";
							u_weapon="sword";
							u_w_pfm = u_w_pfm + ({(: perform_action, "sword.xunlei" :)});
							set("f_w_skill","xunlei-jian");
						break;
					}
				break;
				case 1:
					switch(random(1))
					{
						case 0:
							set_skill("kunlun-zhang",500);									 //���ظ߼����֣������Ʒ�
							map_skill("strike","kunlun-zhang");
							nw_parry="kunlun-zhang";
							prepare_skill("strike","kunlun-zhang");
							u_pfm = u_pfm + ({(: perform_action, "strike.diezhang" :)});     //�����Ʒ�pfm����ɽ����
							u_pfm = u_pfm + ({(: perform_action, "strike.xuebeng" :)});
							set("f_skill","kunlun-zhang");
						break;
					}
					switch(random(1))
					{
						case 0:
							set_skill("liangyi-jian",500);									//���ظ߼����������ǽ���	
							map_skill("sword","liangyi-jian");
							w_parry="liangyi-jian";
//							u_w_pfm = u_w_pfm + ({(: perform_action, "sword.hebi" :)});        	//���ǽ���pfm��˫���ϱ� 
							u_w_pfm = u_w_pfm + ({(: perform_action, "sword.hundun" :)});
							u_w_pfm = u_w_pfm + ({(: perform_action, "sword.xunlei" :)});
							u_weapon="sword";
							set("f_w_skill","liangyi-jian");
						break;
					}					
				break;	
				}
			break;//end case kl	
		case "9y":
			set("family/family_name","�����澭����");
			set_skill("jiuyin-zhengong",500);												//�����ڹ��������湦	
			set_skill("jiuyin-shenfa",500);													//�����Ṧ��������	
			set_skill("daode-jing",200);			
			map_skill("force", "jiuyin-zhengong");
			map_skill("dodge", "jiuyin-shenfa");
			u_f_pfm=u_f_pfm + ({(: exert_function, "yihuen" :)});   
			u_ub_pfm=u_ub_pfm + ({(: exert_function, "zongjue" :)});   							//�����ܾ�
			u_f_pfm=u_f_pfm + ({(: perform_action, "dodge.huanyinbu" :)});      				//������pfm��������
			switch(in_level)
			{
				case 0:
					switch(random(2))
					{
						case 0:
							set_skill("jiuyin-baiguzhua",500);                              //�����ͼ����֣������׹�צ
							map_skill("claw","jiuyin-baiguzhua");
							nw_parry="jiuyin-baiguzhua";
							prepare_skill("claw", "jiuyin-baiguzhua");
							u_pfm=u_pfm + ({(: perform_action, "claw.jiuyin" :)});			//�����׹�צpfm����������צ
							set("f_skill","jiuyin-baiguzhua");       
						break;
						case 1:
							set_skill("cuixin-zhang",500);                             		//�����ͼ����֣�������
							map_skill("strike","cuixin-zhang");
							nw_parry="cuixin-zhang";
							prepare_skill("strike", "cuixin-zhang");
							u_pfm=u_pfm + ({(: perform_action, "strike.cuixin" :)});
							set("f_skill","cuixin-zhang");       							//������pfm�����Ķϳ�
						break;

					}
					switch(random(1))
					{
						case 0:
							set_skill("yinlong-bian",500);                                 //�����ͼ�����������������
							map_skill("whip","yinlong-bian");
							w_parry="yinlong-bian";
							u_w_pfm=u_w_pfm + ({(: perform_action, "whip.chanrao" :)});   	   //����������pfm�����ƾ�
							u_w_pfm=u_w_pfm + ({(: perform_action, "whip.feilong" :)});        //����  
							u_weapon="whip";
							set("f_w_skill","yinlong-bian");
						break;
					}
				break;
				case 1:
					switch(random(3))
					{
						case 0:
							set_skill("jiuyin-shenzhang",500);								//�����߼����֣���������
							map_skill("strike","jiuyin-shenzhang");
							nw_parry="jiuyin-shenzhang";
							prepare_skill("strike","jiuyin-shenzhang");
							u_pfm = u_pfm + ({(: perform_action, "strike.shenzhang" :)});   //��������pfm�����ƶ���
							u_pfm = u_pfm + ({(: perform_action, "strike.yinyang" :)});		//����˫��   
							set("f_skill","jiuyin-shenzhang");     
  						break;
  						case 1:
							set_skill("jiuyin-shenzhua",500);								//�����߼����֣�������צ
							map_skill("claw","jiuyin-shenzhua");
							nw_parry="jiuyin-shenzhua";
							prepare_skill("claw","jiuyin-shenzhua");
							u_pfm = u_pfm + ({(: perform_action, "strike.sanjue" :)});      //������צpfm����������צ
							set("f_skill","jiuyin-shenzhua");
  						break;
   						case 2:
							set_skill("dafumo-quan",500);								    //�����߼����֣����ħȭ
							map_skill("cuff","dafumo-quan");
							nw_parry="dafumo-quan";
							prepare_skill("cuff","dafumo-quan");
							u_pfm = u_pfm + ({(: perform_action, "cuff.fumo" :)});     		//���ħȭpfm����ħ 
							set("f_skill","dafumo-quan");
  						break;
					}
					switch(random(1))
					{
						case 0:
							set_skill("xuanyin-jian",500);									//�����߼���������������	
							map_skill("sword","xuanyin-jian");
							w_parry="xuanyin-jian";
							u_w_pfm = u_w_pfm + ({(: perform_action, "sword.xuanyin" :)});      //��������pfm�������� 	
							u_w_pfm = u_w_pfm + ({(: perform_action, "sword.zhan" :)});			//ն�־�	
							u_weapon="sword";
							set("f_w_skill","xuanyin-jian");
						break;
					}					
				break;	
				}
			break;//end case 9y		
			case "hmg":
				set("family/family_name","��󡹦����");		
				set_skill("hamagong",500);
				map_skill("force","hamagong");
				map_skill("strike","hamagong");
				prepare_skill("strike","hamagong");
				nw_parry="hamagong";
				set("oyf/hamagong",3);
				u_f_pfm = u_f_pfm + ({(: perform_action, "strike.hama" :)});        	
				u_f_pfm = u_f_pfm + ({(: exert_function, "nizhuan" :)});  
				u_ub_pfm = u_ub_pfm + ({(: exert_function, "nizhuan" :)});      	
				set("f_skill","hamagong");
			break;//end hmg
			case "pxj":
				set("family/family_name","�������ܵĴ���");		
				set("gender","����");
				set_skill("pixie-jian",500);
				set_skill("hanbing-zhenqi",500);					//��ɽ�ڹ�����������			
				map_skill("force", "hanbing-zhenqi");
				map_skill("dodge", "pixie-jian");
				map_skill("sword", "pixie-jian");
				u_f_pfm=u_f_pfm + ({(: exert_function, "hanbing" :)});   //��������pfm������
				u_f_pfm=u_f_pfm + ({(: exert_function, "juhan" :)});     //�ۺ�
				u_f_pfm = u_f_pfm + ({(: perform_action, "sword.cimu" :)});        	
				u_f_pfm = u_f_pfm + ({(: perform_action, "dodge.feiying" :)});        	
				u_f_pfm = u_f_pfm + ({(: perform_action, "sword.jue" :)});        	
				w_parry="pixie-jian";
				u_weapon="xiuhua";
				set("f_w_skill","pixie-jian");
			break;//end pxj
			case "jsj":
				set("family/family_name","���߽����Ĵ���");		
				set_skill("zixia-gong",500);								//��ɽ�ڹ�����ϼ��
				set_skill("huashan-shenfa",500);							//��ɽ�Ṧ����ɽ��				
				set_skill("jinshe-jianfa",500);
				set_skill("jinshe-zhangfa",500);
				map_skill("force","zixia-gong");
				map_skill("dodge","huashan-shenfa");
				map_skill("sword","jinshe-jianfa");
				map_skill("strike","jinshe-zhangfa");
				prepare_skill("strike","jinshe-zhangfa");
				nw_parry="jinshe-zhangfa";
				w_parry="jinshe-jianfa";
				set("f_w_skill","jinshe-jianfa");
				set("f_skill","jinshe-zhangfa");
				u_weapon="sword";
				u_f_pfm = u_f_pfm + ({(: perform_action, "sword.kuangwu" :)});        	

				
			break;//end jsj
	}//end whole switch		
}
