/*
Create:i@lishilin.cc 2009-09-21
Description:本js文件为后台提供各种操作方法
*/


//为表格增加样式、排序、单双击事件及全选事件
$(document).ready(
	function(){
		var o = $("table#tbContent");
		if(o.length == 0)
			return;
		
		//数据行样式、单双击事件
		$("#tbdDataList>tr").each(
			function(){
				//行单击，选中
				$(this).click(
					function(){
						var obj = window.event ? event.srcElement : arguments[0].target;
						if(obj.tagName == "TR" || obj.tagName == "TD"){
							var cbx = $(this).find("input[name=cbxData]");
							if(cbx.length == 0)
								return;
							cbx[0].checked=cbx[0].checked ? false : true;
						}
					}
				);
				//行双击，打开编辑页面
				$(this).dblclick(
					function(){
						DblEdit(this);
					}
				);
			}
		);
		
		//全选/全不选
		$("#cbxAll").click(
			function(){
				if(this.checked)
				{
					$("input[name=cbxData]").each(
						function(){
							this.checked = true;
						}
					);
				}
				else
				{
					$("input[name=cbxData]").each(
						function(){
							this.checked = false;
						}
					);
				}
			}
		);
		
		//表头行排序
		o.find("th[axis]").each(
			function(){
				var th = $(this);
				th.attr("title","点击按"+th.text().Trim()+"进行排序");
				//设置样式
				var order = decodeURIComponent(GetRequest("orderby",""));
				if(order != ""){
					var oar = order.split(" ");//ID desc
					if(oar.length != 2)
						return;
					if(oar[0].toLowerCase() == th.attr("axis").toLowerCase())
					{
						//设置当前排序样式
						if(oar[1].Trim().toLowerCase() == "desc"){
							th.html(th.text().Trim() + "&nbsp;&#9650;")
						}
						else{
							th.html(th.text().Trim() + "&nbsp;&#9660;")
						}
					}
				}
				//排序按钮点击
				th.click(function(){
					var axis = $(this).attr("axis");
					if(order != ""){
						var oar = order.split(" ");//ID desc
						if(oar.length != 2){//参数错误，按首次进行排序的逻辑
							LocationToMeParam("orderby=" + encodeURIComponent( axis + " asc"));
							return;
						}
						if(oar[0].Trim().toLowerCase() == axis.toLowerCase().Trim()){//当前排序参数名一样
							if(oar[1].Trim().toLowerCase() == "desc"){
								LocationToMeParam("orderby=" + encodeURIComponent( axis + " asc"));
							}
							else{
								LocationToMeParam("orderby=" + encodeURIComponent( axis + " desc"));
							}
						}
						else{//不一样，按首次排序的逻辑
							LocationToMeParam("orderby=" + encodeURIComponent( axis + " asc"));
						}
					}
					else{//从来没有order参数，按首次排序的逻辑
						LocationToMeParam("orderby=" + encodeURIComponent( axis + " asc"));
					}
				});
			}
		);
	}
);

//后台专用的浮动编辑层
function EditLayer(text, width){
	var s = new Screen();
	//创建遮罩层
	var mask = $("#Mask");
	if(mask.length == 0)
	{
		mask = CreateStateDiv("Mask");
		mask.style.border = "0px";
		mask.style.filter = "alpha(opacity=80)";
		mask.style.opacity = "0.8";
		mask.style.zIndex = "1000";
		mask.style.backgroundImage = "none";
		mask.style.backgroundColor = "#fefefe";
		mask.style.position = "absolute";
		mask.style.top = 0;
		mask.style.left = 0;
		mask.style.width = Math.max(s.ClientWidth,s.ScrollWidth) + "px";
		mask.style.height = Math.max(s.ClientHeight,s.ScrollHeight) + "px";
		mask.style.display = "inline";
		$(mask).css("-moz-opacity","0.8");
		$(mask).click(function(){ CloseLayer(); });
		AppendElement(mask);
	}
	else
	{
		mask.css("display","inline");
	}

	var state = $("#Tranning")[0];
	if (state == null) {
		state = CreateStateDiv("Tranning");
		AppendElement(state);
	}
	var swidth = (width == null || width == "" || width == 0) ? 600 : width;
	
	var content = ['<div style="color:#153c64;font-weight:bold;font-size:14px;padding:7px 0 0 12px;cursor:move;" onmouseover="DivMove(\'Tranning\');">',
	'<span style="position:absolute;top:4px;right:5px;">',
	'<img src="/Analy/Images/System/d_close.gif" width="21" height="19" style="border:0;cursor:pointer;" title="关闭" alt="关闭" onclick="CloseLayer();" /></span>',
	'网页对话框</div>',
	'<div style="padding: 25px; line-height: 24px;">',
	text,
	'</div>',
	'<div style="height:27px;background:url(/Analy/Images/System/d_bottom.gif) repeat-x left top; border-top:1px solid #e1e1e1;text-align:center;padding-top:4px;">',
	'<img src="/Analy/Images/System/d_btn.gif" style="border:0;cursor:pointer;" title="关闭" alt="关闭" onclick="CloseLayer();" />',
	'</div>'].join("");
	
	$(state).css("display","inline").css("width",swidth + "px");
	$(state).html(content);
	
	var stop = s.ScrollTop + (s.ClientHeight - $(state).attr("clientHeight")) / 2;
	if(stop < 0)
		stop = 20;
	var sleft = s.ScrollLeft + ((s.ClientWidth - width) / 2);
	if(sleft < 0)
		sleft = 20;
	
	$(state).css("top", stop).css("left",sleft)
}

//全局变量RefreshPage定义关闭弹出层时是否刷新页面
var RefreshPage = false;

//关闭弹出层
function CloseLayer()
{
	HiddenState("Mask", 1);
	HiddenState("Tranning", 1);
	if(RefreshPage)
		location.href=location.href;
}

//检测页面是否已定义ActionUrl和Target变量
function CheckDefine()
{	
//	if(ActionUrl == null || ActionUrl == 'undefine' || ActionUrl == "")
//	{
//		Msg("请定义ActionUrl变量！",300);
//		return false;
//	}
	if(Target == null || Target == 'undefine' || Target == "")
		Target = "_blank";
	if(DialogWidth == null || DialogWidth == 'undefine' || DialogWidth == 0)
		DialogWidth = 500;
	if(DialogHeight == null || DialogHeight == 'undefine' || DialogHeight == 0)
		DialogHeight = 400;
	return true;
}

//添加数据的方法
function Add()
{
	if(!CheckDefine())
		return;
	
	if(Target.toLowerCase() == "_blank")
	{
		var url = SetUrlParam(ActionUrl,"reurl=" + encodeURIComponent(location.href));
		LocationTo(url);
	}
	else
	{
		EditLayer("<iframe src='"+ActionUrl+"' height='"+DialogHeight+"' width='100%' border='0' frameborder='0' scrolling='no' />",DialogWidth);
	}
}

//修改数据按钮的方法
function Edit()
{
	if(!CheckDefine())
		return;
		
	var list = GetAllChecked();
	if(list.length <= 0)
	{
		Msg("您还没有选中任何数据。<br />提示：在您要修改的数据行上双击鼠标可直接进入编辑页面。",300);
		return;
	}
	
	if(list.length > 1)
	{
		Msg("一次只能编辑一条记录，您选择了"+list.length+"条，请重新选择。",300);
		return;
	}
	
	var url = SetUrlParam(ActionUrl, "params=" + list.toString());
	
	if(Target.toLowerCase() == "_blank")
	{
		url = SetUrlParam(url,"reurl=" + encodeURIComponent(location.href));
		LocationTo(url);
	}
	else
	{
		EditLayer("<iframe src='"+url+"' height='"+DialogHeight+"' width='100%' border='0' frameborder='0' scrolling='no' />",DialogWidth);
	}
}

//管理员修改自己资料的弹出层
function AdminEditMe()
{
	EditLayer("<iframe src='/Analy/EditMe.aspx' height='200' width='100%' border='0' frameborder='0' scrolling='no' />",700);
}

//双击修改数据的方法（仅读取当前行的id值）
function DblEdit(tr)
{
	if(!CheckDefine())
		return;
	if(tr == null || tr.tagName != "TR")
		return;
	var cbx = $(tr).find("input[name=cbxData]");
	if(cbx.length == 0)
		return;
	var param = cbx.val().Trim();
	if(isNaN(param)||ActionUrl==null)
		return;
	var url = SetUrlParam(ActionUrl, "params=" + param);
	
	if(Target.toLowerCase() == "_blank")
	{
		url = SetUrlParam(url,"reurl=" + encodeURIComponent(location.href));
		LocationTo(url);
	}
	else
	{
		EditLayer("<iframe src='"+url+"' height='"+DialogHeight+"' width='100%' border='0' frameborder='0' scrolling='no' />",DialogWidth);
	}
}

//删除的方法
function Delete()
{
	var list = GetAllChecked();
	if(list.length <= 0)
	{
		Msg("您还没有选中任何数据。",300);
		return;
	}
	
	if(!confirm("您确定要删除您选中的数据吗？\r\n注意：此操作不可恢复！"))return;
	
	var reurl = encodeURIComponent(encodeURIComponent(location.href));//由于系统自带UrlDecode解码，所以要让url包含两次编码的网址时，需要多增加一次编码
	var url = SetUrlParam(location.href,"action=del");
	url = SetUrlParam(url, "params=" + list.toString());
	url = SetUrlParam(url,"reurl=" + reurl);
	LocationTo(url);
}

//导出所选数据的方法
function ExportPage()
{
	var list = GetAllChecked();
	if(list.length <= 0)
	{
		if(confirm("您没有选中任何数据，请问是要导出全部数据吗？"))
		{
			Export();
		}
		return;
	}
	
	var url = SetUrlParam(location.href,"action=exportpage");
	url = SetUrlParam(url, "params=" + list.toString());
	LocationTo(url);
}

//导出全部数据的方法
function Export()
{
	var url = SetUrlParam(location.href,"action=export");
	LocationTo(url);
}

//取得所有选中的行
function GetAllChecked()
{
	var arr = $.makeArray($("input[name=cbxData]:checked"));
	if(arr.length <= 0)
		return new Array();
	var result = new Array();
	for(var i=0;i<arr.length;i++)
	{
		result.push(arr[i].value.Trim());
	}
	return result;
}

//表单页标签切换
function SetForms(index)
{
	var ol = $("div.tab").children("ul").find("li");
	var fl = $("div.forms").children("ul");
	for(var i=0;i<ol.length;i++)
	{
		if(ol[i].className == "tabinfo")
			continue;
		ol[i].className = i == index ? "active" : "";
		fl[i].className = i == index ? "formShow" : "formHidden";
	}
}
//子标签切换，可支持无限极
function SetSubForms(index,obj)
{
	var ol = $(obj).parent("ul").parent("div.subtab").find("li");
	var fl = $(obj).parent("ul").parent("div.subtab").siblings("div.subforms").children("ul");
	for(var i=0;i<ol.length;i++)
	{
		ol[i].className = i == index ? "subactive" : "";
		fl[i].className = i == index ? "subformshow" : "subformhidden";
	}
}

/* 以下为jquery插件：SuperFish下拉菜单 */

/*
* Superfish v1.4.8 - jQuery menu widget
* Copyright (c) 2008 Joel Birch
*
* Dual licensed under the MIT and GPL licenses:
* 	http://www.opensource.org/licenses/mit-license.php
* 	http://www.gnu.org/licenses/gpl.html
*
* CHANGELOG: http://users.tpg.com.au/j_birch/plugins/superfish/changelog.txt
*/

; (function($)
{
	$.fn.superfish = function(op)
	{

		var sf = $.fn.superfish,
			c = sf.c,
			$arrow = $(['<span class="', c.arrowClass, '"> &#187;</span>'].join('')),
			over = function()
			{
				var $$ = $(this), menu = getMenu($$);
				clearTimeout(menu.sfTimer);
				$$.showSuperfishUl().siblings().hideSuperfishUl();
			},
			out = function()
			{
				var $$ = $(this), menu = getMenu($$), o = sf.op;
				clearTimeout(menu.sfTimer);
				menu.sfTimer = setTimeout(function()
				{
					o.retainPath = ($.inArray($$[0], o.$path) > -1);
					$$.hideSuperfishUl();
					if (o.$path.length && $$.parents(['li.', o.hoverClass].join('')).length < 1) { over.call(o.$path); }
				}, o.delay);
			},
			getMenu = function($menu)
			{
				var menu = $menu.parents(['ul.', c.menuClass, ':first'].join(''))[0];
				sf.op = sf.o[menu.serial];
				return menu;
			},
			addArrow = function($a) { $a.addClass(c.anchorClass).append($arrow.clone()); };

		return this.each(function()
		{
			var s = this.serial = sf.o.length;
			var o = $.extend({}, sf.defaults, op);
			o.$path = $('li.' + o.pathClass, this).slice(0, o.pathLevels).each(function()
			{
				$(this).addClass([o.hoverClass, c.bcClass].join(' '))
					.filter('li:has(ul)').removeClass(o.pathClass);
			});
			sf.o[s] = sf.op = o;

			$('li:has(ul)', this)[($.fn.hoverIntent && !o.disableHI) ? 'hoverIntent' : 'hover'](over, out).each(function()
			{
				if (o.autoArrows) addArrow($('>a:first-child', this));
			})
			.not('.' + c.bcClass)
				.hideSuperfishUl();

			var $a = $('a', this);
			$a.each(function(i)
			{
				var $li = $a.eq(i).parents('li');
				$a.eq(i).focus(function() { over.call($li); }).blur(function() { out.call($li); });
			});
			o.onInit.call(this);

		}).each(function()
		{
			var menuClasses = [c.menuClass];
			if (sf.op.dropShadows && !($.browser.msie && $.browser.version < 7)) menuClasses.push(c.shadowClass);
			$(this).addClass(menuClasses.join(' '));
		});
	};

	var sf = $.fn.superfish;
	sf.o = [];
	sf.op = {};
	sf.IE7fix = function()
	{
		var o = sf.op;
		if ($.browser.msie && $.browser.version > 6 && o.dropShadows && o.animation.opacity != undefined)
			this.toggleClass(sf.c.shadowClass + '-off');
	};
	sf.c = {
		bcClass: 'sf-breadcrumb',
		menuClass: 'sf-js-enabled',
		anchorClass: 'sf-with-ul',
		arrowClass: 'sf-sub-indicator',
		shadowClass: 'sf-shadow'
	};
	sf.defaults = {
		hoverClass: 'sfHover',
		pathClass: 'overideThisToUse',
		pathLevels: 1,
		delay: 800,
		animation: { opacity: 'show' },
		speed: 'normal',
		autoArrows: true,
		dropShadows: true,
		disableHI: true, 	// true disables hoverIntent detection
		onInit: function() { }, // callback functions
		onBeforeShow: function() { },
		onShow: function() { },
		onHide: function() { }
	};
	$.fn.extend({
		hideSuperfishUl: function()
		{
			var o = sf.op,
				not = (o.retainPath === true) ? o.$path : '';
			o.retainPath = false;
			var $ul = $(['li.', o.hoverClass].join(''), this).add(this).not(not).removeClass(o.hoverClass)
					.find('>ul').hide().css('visibility', 'hidden');
			o.onHide.call($ul);
			return this;
		},
		showSuperfishUl: function()
		{
			var o = sf.op,
				sh = sf.c.shadowClass + '-off',
				$ul = this.addClass(o.hoverClass)
					.find('>ul:hidden').css('visibility', 'visible');
			sf.IE7fix.call($ul);
			o.onBeforeShow.call($ul);
			$ul.animate(o.animation, o.speed, function() { sf.IE7fix.call($ul); o.onShow.call($ul); });
			return this;
		}
	});

})(jQuery);