// 1/28/2002	by augx@sj

void change_short()
{
	if(query("mode")==1) {
		set("short","大清战船");
		set("long",@long
这是艘巨大的战船，是由整条整条的东北百年古桐木拼装而成，整个外壳
新涂了防火油，显的更是光亮。主桅杆由整颗三人合抱之千年古桐制成，坚固
异常，即使炮弹也无法轻易毁损，桅杆顶一面巨大的大清龙旗随风翻腾，气派
非凡。此战船虽然巨大，但为木质，极轻，中仓更是设置无数木浆，因此速度
极快，灵敏异常。前甲板上稳坐一尊红衣巨炮，射程极远，为当世之利器。
long);
	}
	else {
		set("short","舢板");
		set("long",@long
这是艘舢板，由十多根木料捆绑而成，还算结实，能够经受一般的风浪。
上面用帆布竖着一面直角帆，提供动力。舢板因为很小巧，速度很快，且很不
容易被炮火击中。
long);
	}
}
