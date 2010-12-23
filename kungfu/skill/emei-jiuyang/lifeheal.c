// Exert: LifeHeal.c
// Date : AHA 97/06/22

#include <ansi.h>

int exert(object me, object target)
{
  string he;

  if(!objectp(target) || 
     (environment(me)!=environment(target)) ||
     !living(target)
    )
    return notify_fail("ÕâÀïÃ»ÓÐÕâ¸öÈË¡£\n");
   
  if(target == me )
     return notify_fail("ÄãÏëÌæ×Ô¼ºÁÆÉË£¬¿ÉÊÇÔË¹¦µÄ·½·¨²»¶Ô¡£\n");
  
  he = target->name();

  if( me->is_fighting() )
      return notify_fail("Õ½¶·ÖÐÎÞ·¨Ìæ±ðÈËÁÆÉË£¡\n");
  if( target->is_fighting() )
      return notify_fail(he+"ÕýÔÚÕ½¶·ÖÐ£¬ÎÞ·¨ÁÆÉË£¡\n");
  if( target->is_busy() )
      return notify_fail(he+"ÕýÃ¦×ÅÄØ¡£\n");
  if ((int)me->query_skill("emei-jiuyang", 1) < 30)
      return notify_fail("ÄãµÄ¾ÅÑô¹¦ÐÞÎªÌ«µÍ£¬»¹ÊÇºÃºÃÁ·¹¦°É¡£\n");
  if( (int)me->query("neili") < 50 ) 
      return notify_fail("ÄãµÄÕæÆø²»×ã¡£\n");

  if( (int)target->query("eff_qi") >= (int)target->query("max_qi") )
      return notify_fail(he+"ÏÖÔÚ²¢Ã»ÓÐÊÜÉËÑ½£¡\n");

  if( (int)target->query("eff_qi") < (int)target->query("max_qi") / 3 )
      return notify_fail(
               he+"ÊÜÉËÌ«ÖØÁË£¬Ö»ÅÂÒ»ÊÜµ½ÕæÆøÕðµ´±ã»áÓÐÉúÃüÎ£ÏÕ£¡\n");
 
  if(target->query("gender") != "ÖÐÐÔ" &&
     target->query("gender") != me->query("gender") &&
     me->query("class")=="bonze")
       command("say °¢ÃÖÍÓ·ð£¡ÉÆÔÕ£¡ÉÆÔÕ£¡ÎªÁË¾ÈÈË£¬"
               +RANK_D->query_self(me)+"Ò²¹Ë²»µÃÄÐÅ®Ö®·ÀÁË¡£\n");

  write( HIW "ÄãÅÌÍÈ×øÏÂ£¬Ò»ÊÖ°´ÔÚ"+he+"µÄÐ¡¸¹£¬ÁíÒ»ÊÖ°´ÔÚ"+he+"µÄºóÑü£¬\n"
             "ÆøÄýµ¤Ìï£¬¿ªÊ¼Îª"+he+"ÁÆÉË¡£\n" NOR);
  message("vision",
     me->name() + HIR"µÄÁ³Ô½À´Ô½ºì£¬"+HIW"Í·¶¥¿ªÊ¼³öÏÖ°×Îí£¬°×ÎíÔ½À´Ô½Å¨£¬\n"
           "Öð½¥½«"+me->name()+"ºÍ"+he+"Î§ÁËÆðÀ´¡£\n"NOR     
          + me->name() + "ÔË¹¦Íê±Ï£¬³¤³¤µØÍÂÁËÒ»¿ÚÆø¡£"
          +he+"Á³É«¿´ÆðÀ´ºÃÁËÐí¶à¡£\n",
     environment(me), me);
  
  target->receive_curing("qi", 20 + (int)me->query_skill("force")/5 );
  me->add("neili", -50);
  return 1;
}

ÿ
