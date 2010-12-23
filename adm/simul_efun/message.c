// message.c

varargs object snoop( object snooper, object snoopee )
{
	if (wiz_level(snooper) < wiz_level(snoopee))
		return 0;
	if (objectp(snoopee))
		return efun::snoop(snooper, snoopee);
	return efun::snoop(snooper);
}

int living(object me)
{
	if (me->query("disable_type")) return 0;
	return efun::living(me);
}

varargs void message_vision(string msg, object me, object you)
{
	string my_gender, your_gender, my_name, your_name;
	string str1, str2, str3;

	my_name= me->name();
	my_gender = me->query("gender");
	str1 = replace_string(msg,  "$P", gender_self(my_gender));
	str1 = replace_string(str1, "$N", gender_self(my_gender));
	str3 = replace_string(msg,  "$P", gender_pronoun(my_gender));
	str3 = replace_string(str3, "$N", my_name);
	if( you ) {
		your_name= you->name();
		your_gender= you->query("gender");
		str2 = replace_string(msg,  "$P", gender_pronoun(my_gender));
		str2 = replace_string(str2, "$N", my_name);
		str2 = replace_string(str2, "$p", gender_self(your_gender));
		str2 = replace_string(str2, "$n", gender_self(your_gender));
		message("vision", str2, you);
		str1 = replace_string(str1, "$p", gender_pronoun(your_gender));
		str1 = replace_string(str1, "$n", your_name);
		str3 = replace_string(str3, "$p", gender_pronoun(your_gender));
		str3 = replace_string(str3, "$n", your_name);
	}
	message("vision", str1, me);
	message("vision", str3,  environment(me), ({ me, you}) );
}

void tell_object(object ob, string str)
{
	message("tell_object", str, ob);
}

varargs void tell_room(mixed ob, string str, object *exclude)
{
	if( ob ) message("tell_room", str, ob, exclude);
}

void shout(string str)
{
	message("shout", str, users(), this_player());
}

void write(string str)
{
	if( this_player() )
		message("write", str, this_player());
	else if( previous_object() )
		message("write", str, previous_object());
	else
		efun::write(str);
}

varargs void say(string str, mixed exclude)
{
	object ob = previous_object();

	if (ob->is_character() && !living(ob) && base_name(ob) != CORPSE_OB)
		return;
	message("say", str, environment(ob), ob);
}
