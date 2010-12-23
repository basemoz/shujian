// killer's skill by cool 98.6.11
// Modify By River 99/03/16
string *k_force =({ 
                        "qiantian-yiyang",
                        "huntian-qigong",
                        "yijin-jing",
                        "bihai-chaosheng",
                        "linji-zhuang",
                        "yunu-xinjing",
                        "xiantian-gong",
                        "zixia-gong",
                        "xuantian-wuji",
                        "guiyuan-tunafa",
                        "yinyun-ziqi",
                        "shenghuo-shengong",
                        "huagong-dafa",
                        "shenyuan-gong",});
string *k_dodge =({ 
                        "piaoyi-shenfa",
                        "suibo-zhuliu",
                        "tianlong-xiang",
                        "tiyunzong",
                        "shaolin-shenfa",
                        "yunu-shenfa",
                        "kunlun-shenfa",
                        "shuishangpiao",
                        "yanling-shenfa",
                        "zhaixingshu", 
                        "xiaoyaoyou",
                        "anying-fuxiang",});

mapping *skill1=({
/*cuff*/
      (["t_skill" :              "poyu-quan",
         "b_skill" :              "cuff",]),
       (["t_skill" :              "wudang-quan",
         "b_skill" :              "cuff",]),
		  (["t_skill" :              "duanjia-quan",
         "b_skill" :              "cuff",]),  
        (["t_skill" :              "taizu-quan",
         "b_skill" :              "cuff",]),  
        (["t_skill" :              "luohan-quan",
         "b_skill" :              "cuff",]),  
        (["t_skill" :              "wenjia-quan",
         "b_skill" :              "cuff",]), 
		  (["t_skill" :              "fuhu-quan",
         "b_skill" :              "cuff",]), 
/*strike*/
       (["t_skill" :              "hunyuan-zhang",
          "b_skill" :              "strike",]),  
        (["t_skill" :              "qingyan-zhang",
         "b_skill" :              "strike",]),  
        (["t_skill" :              "hanbing-mianzhang",
         "b_skill" :              "strike",]),  
        (["t_skill" :              "xingyi-zhang",
         "b_skill" :              "strike",]),  
        (["t_skill" :              "sanhua-zhang",
         "b_skill" :              "strike",]),  
        (["t_skill" :              "weituo-zhang",
         "b_skill" :              "strike",]),  
        (["t_skill" :              "luoying-zhang",
         "b_skill" :              "strike",]),  
        (["t_skill" :              "kunlun-zhang",
         "b_skill" :              "strike",]), 
        (["t_skill" :              "tiangang-zhang",
         "b_skill" :              "strike",]),
/*hand*/
        (["t_skill" :              "fengyun-shou",
         "b_skill" :              "hand",]),
        (["t_skill" :              "yingzhua-shou",
         "b_skill" :              "hand",]),
        (["t_skill" :              "suohou-shou",
         "b_skill" :              "hand",]),
/*leg*/
        (["t_skill" :              "shaolin-tantui",
         "b_skill" :              "leg",]),
        (["t_skill" :              "xuanfeng-tui",
         "b_skill" :              "leg",]),
/*finger*/      
        (["t_skill" :              "canhe-zhi",
         "b_skill" :              "finger",]),
        (["t_skill" :              "mohe-zhi",
         "b_skill" :              "finger",]),
        (["t_skill" :              "nianhua-zhi",
         "b_skill" :              "finger",]),
/*claw*/        
        (["t_skill" :              "yingzhua-gong",
         "b_skill" :              "claw",]),
        (["t_skill" :              "jimie-zhua",
         "b_skill" :              "claw",]),
		  (["t_skill" :              "tianwang-zhua",
         "b_skill" :              "claw",]),
});

mapping *skill2=({
/*cuff*/
       (["t_skill" :              "taiji-quan",
         "b_skill" :              "cuff",]),
        (["t_skill" :             "taizu-quan",
         "b_skill" :              "cuff",]),  
        (["t_skill" :             "jingang-quan",
         "b_skill" :              "cuff",]),  
        (["t_skill" :             "kongming-quan",
         "b_skill" :              "cuff",]), 
        (["t_skill" :             "poyu-quan",
         "b_skill" :              "cuff",]),  
        (["t_skill" :             "meinu-quanfa",
         "b_skill" :              "cuff",]), 
        (["t_skill" :             "wenjia-quan",
         "b_skill" :              "cuff",]), 
/*strike*/
       (["t_skill" :              "hunyuan-zhang",
         "b_skill" :              "strike",]),
       (["t_skill" :              "huagu-mianzhang",
         "b_skill" :              "strike",]),
       (["t_skill" :             "wudang-mianzhang",
          "b_skill" :              "strike",]),  
        (["t_skill" :             "qingyan-zhang",
         "b_skill" :              "strike",]),  
        (["t_skill" :             "hanbing-mianzhang",
         "b_skill" :              "strike",]),  
        (["t_skill" :             "xingyi-zhang",
         "b_skill" :              "strike",]),  
        (["t_skill" :             "sanhua-zhang",
         "b_skill" :              "strike",]),  
        (["t_skill" :             "banruo-zhang",
         "b_skill" :              "strike",]),  
        (["t_skill" :             "chousui-zhang",
         "b_skill" :              "strike",]),  
        (["t_skill" :             "hunyuan-zhang",
         "b_skill" :              "strike"]),
        (["t_skill" :             "jinding-mianzhang",
         "b_skill" :              "strike"]),
        (["t_skill" :             "jinshe-zhangfa",
         "b_skill" :              "strike"]),
        (["t_skill" :             "luoying-zhang",
         "b_skill" :              "strike",]),  
        (["t_skill" :             "kunlun-zhang",
         "b_skill" :              "strike",]), 
        (["t_skill" :             "tiangang-zhang",
         "b_skill" :              "strike",]),
        (["t_skill" :             "sixiang-zhang",
         "b_skill" :              "strike",]),
        (["t_skill" :             "tiezhang-zhangfa",
         "b_skill" :              "strike",]),
        (["t_skill" :              "huoyan-dao",
         "b_skill" :              "strike",]), 
		 (["t_skill" :             "songyang-zhang",
         "b_skill" :              "strike",]), 
		 (["t_skill" :             "hanbing-shenzhang",
         "b_skill" :              "strike",]),  
 
/*hand*/
       (["t_skill" :              "dashou-yin",
         "b_skill" :              "hand",]), 
        (["t_skill" :              "yingzhua-shou",
         "b_skill" :              "hand",]),
        (["t_skill" :              "suohou-shou",
         "b_skill" :              "hand",]),
        (["t_skill" :              "jieshou-jiushi",
         "b_skill" :              "hand",]),
        (["t_skill" :              "juehu-shou",
         "b_skill" :              "hand",]),
        (["t_skill" :              "lanhua-shou",
         "b_skill" :              "hand",]),
        (["t_skill" :              "qianye-shou",
         "b_skill" :              "hand",]),
		  (["t_skill" :              "dashou-yin",
         "b_skill" :              "hand",]), 

/*leg*/
        (["t_skill" :              "ruying-suixingtui",
         "b_skill" :              "leg",]),
        (["t_skill" :              "xuanfeng-tui",
         "b_skill" :              "leg",]),
		  (["t_skill" :              "shenlong-tuifa",
         "b_skill" :              "leg",]),
		  (["t_skill" :              "chuanyun-tui",
         "b_skill" :              "leg",]),
/*finger*/
        (["t_skill" :              "yizhi-chan",
         "b_skill" :              "finger",]),
        (["t_skill" :              "tanzhi-shentong",
         "b_skill" :              "finger",]),
        (["t_skill" :              "canhe-zhi",
         "b_skill" :              "finger",]),
        (["t_skill" :              "nianhua-zhi",
         "b_skill" :              "finger",]),
/*claw*/
        (["t_skill" :              "yingzhua-gong",
         "b_skill" :              "claw",]),
        (["t_skill" :              "jimie-zhua",
         "b_skill" :              "claw",]),
        (["t_skill" :              "longzhua-gong",
         "b_skill" :              "claw",]),
		 (["t_skill" :              "tianwang-zhua",
         "b_skill" :              "claw",]),
});
