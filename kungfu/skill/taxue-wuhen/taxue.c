// 玄天无极-踏雪无痕
// 脚踏白雪身无痕
// modify by cmkj 2003.8.19
// update增加飞跃后效果
#include <ansi.h>
inherit F_CLEAN_UP;

int exert(object me, object target)
{
        int skill;

        if ((int)me->query_skill("taxue-wuhen", 1) < 100)
                return notify_fail("你的踏雪无痕修为还不够。\n");
        if((int)me->query("max_neili")<1000)
                return notify_fail("你的内力修为太差，多多打坐吧。\n");
        if( (int)me->query("neili") < 500 )
                return notify_fail("你的真气不够。\n");
        if (me->query_temp("kl/taxue"))
                return notify_fail("你已经在使用踏雪无痕了。\n");
        

        skill = me->query_skill("taxue-wuhen",1) / 3;

        message_vision(CYN "$N双手虚按丹田，展开轻功，身子轻飘飘的，宛似凌空飞行！\n" NOR, me);
        
        me->add_temp("apply/dodge", skill);
        me->set_temp("kl/taxue", skill);
        me->add("neili", -150);
          me->start_call_out( (: call_other, __FILE__, "remove_effect", me :), skill/2 );
        if( me->is_fighting() ) me->start_busy(2);

        return 1;
}
void remove_effect(object me)
{
        int amount;
        
        if ( me && (int)me->query_temp("kl/taxue") ) {
                amount = me->query_temp("kl/taxue");
                me->add_temp("apply/dodge", - amount);
                me->delete_temp("kl/taxue");
               message_vision(CYN "$N散去丹田聚集的内力，立定了脚步，身法回复了正常！\n" NOR, me);
        }
}
