<%@ Control Language="C#" AutoEventWireup="true" CodeBehind="WebTop.ascx.cs" Inherits="Bzw.Web.Public.WebTop" %>
    <script type="text/javascript" src="/Public/Js/common.js"></script>
<div id="fla" >
    <img src="/Images/top_fla01.jpg" alt="" />
</div>
<div id="header" >
    <h1 style=" margin-top:0px; padding-top:0px;">
        <a href="/Default.aspx">
            <img src="/Images/logo01.jpg" alt="" border="0" /></a></h1>
    <div id="gnb" class="r30">
        <ul class="fr">
            <li style="padding-top: 4px;"><a href="/Manage/Reg.aspx" class="link01">注册</a></li>
            <li style="padding-top: 4px;"><a href="/Manage/Login.aspx" class="link01">帐号登入</a></li>
            <li  style=" overflow:hidden; height:20px;">
        
                <div id="bdshare" class="bdshare_t bds_tools get-codes-bdshare">
                    <span class="bds_more" style="color: White;">分享到：</span> <a class="bds_qzone"></a>
                    <a class="bds_tsina"></a><a class="bds_tqq"></a><a class="bds_renren"></a>
                </div>

                <script type="text/javascript" id="bdshare_js" data="type=tools&amp;mini=1"></script>

                <script type="text/javascript" id="bdshell_js"></script>

                <script type="text/javascript">
                    document.getElementById("bdshell_js").src = "http://bdimg.share.baidu.com/static/js/shell_v2.js?cdnversion=" + new Date().getHours();
</script>

 
            </li>
        </ul>
    </div>
    <div class="clear"></div>
    <div id="yxtj"  >
        <p>
            <img src="/Images/top_img01.jpg" alt="" /></p>
        <div class="tj">
            <p class="fl" id="J_prev">
                <a href="javascript:" onclick="pre()">
                    <img src="/Images/left01.jpg" alt="" /></a></p>
            <ul id="gametop"   >
           
            </ul>
            <p id="J_next">
                <a href="javascript:" style="margin-left: 3px; float:right" onclick=" nex()">
                    <img src="/Images/right01.jpg" alt="" border="0" /></a></p>
        </div>
        <p>
            <img src="/Images/top_img02.jpg" alt="" /></p>
    </div>
    
    <style type="text/css">


.main_navi {position: absolute; text-align:left; padding-top:0px; }
.main_navi li {list-style-type: none; float: left; }

.navi {	background: url("/images/nav.jpg") no-repeat; height: 51px; width:824px; line-height: 260px; overflow: hidden; float: left;  }
.navi_01 {	width: 74px;} /*首页*/
.navi_02 {	background-position: -74px 0px; width: 94px;}/*游戏下载*/
.navi_03 {	background-position: -168px 0px; width: 93px;}/*精品ID*/
.navi_04 {	background-position: -261px 0px; width: 94px;}/*账户充值*/
.navi_05 {	background-position: -355px 0px; width: 94px;}/*新闻中心*/
.navi_06 {	background-position: -449px 0px; width: 94px;} /*推广员*/
.navi_07 {	background-position: -543px 0px; width: 93px;} /*排行榜*/
.navi_08 {	background-position: -636px 0px; width: 94px;} /*兑奖中间*/
.navi_09 {	background-position: -730px 0px; width: 93px;} /*客服中心*/

 
.navi_01:hover {	background-position: 0px -51px;  }
.navi_02:hover {	background-position: -74px -51px; }
.navi_03:hover {	background-position: -168px -51px; }
.navi_04:hover {	background-position: -261px -51px; }
.navi_05:hover {	background-position: -355px -51px; }
.navi_06:hover {	background-position: -449px -51px; } 
.navi_07:hover {	background-position: -543px -51px; } 
.navi_08:hover {	background-position: -636px -51px; } 
.navi_09:hover {	background-position: -730px -51px; } 
 
.navi_01ed {	background-position: 0px -51px;  width: 74px;}
.navi_02ed {	background-position: -74px -51px; width: 94px;}
.navi_03ed {	background-position: -168px -51px; width: 93px;}
.navi_04ed {	background-position: -261px -51px; width: 94px;}
.navi_05ed {	background-position: -355px -51px; width: 94px;}
.navi_06ed {	background-position: -449px -51px; width: 94px;} 
.navi_07ed {	background-position: -543px -51px; width: 93px;} 
.navi_08ed {	background-position: -636px -51px; width: 94px;} 
.navi_09ed {	background-position: -730px -51px; width: 93px;} 

    </style>
    
    
    
    
    
    
    <div id="top_menu">
				<ul class="main_navi">
					<li><a class="navi navi_01" id="nav1" href="/Default.aspx">首页</a></li>
					<li><a class="navi navi_02" id="nav2" href="/Down.aspx" >游戏下载</a></li>
					<li><a class="navi navi_03" id="nav3" href="/Manage/FineryID.aspx">精品ID</a></li>
					<li><a class="navi navi_04" id="nav4" href="/Manage/Pay/Default.aspx">账户充值</a></li>
					<li><a class="navi navi_05" id="nav5" href="/NewsList.aspx">新闻中心</a></li>
					<li><a class="navi navi_06" id="nav6" href="/Promoter.aspx">推广员</a></li>
					<li><a class="navi navi_07" id="nav7" href="/RankMoney.aspx">排行榜</a></li>
					<li><a class="navi navi_08" id="nav8" href="/JiangPin.aspx">兑奖中间</a></li>
					<li><a class="navi navi_09" id="nav9" href="/Service.aspx">客服中心</a></li>
					
				</ul>
	</div>
    
   
    <script type="text/javascript">
        var pagetype = <%=pageType %>;
        if (pagetype !=null)
        {
            $("#nav<%=pageType %>").removeClass().addClass("navi navi_0<%=pageType %>ed");
        }
    </script>
   <!-- 
    <div id="top_menu1"   >
        <ul class="ks-switchable-content">
            <li><a href="/Default.aspx" onmouseover="menu_over(1,<%=pageType %>)" onmouseout="menu_out(1,<%=pageType %>)"
                onfocus="menu_over(1,<%=pageType %>)">
                <img src='/Images/top_menu01<%= pageType==1?"on":"off" %>.jpg' alt="首页" id="m1" border="0" /></a></li>
            <li><a href="/Down.aspx" onmouseover="menu_over(2,<%=pageType %>)" onmouseout="menu_out(2,<%=pageType %>)"
                onfocus="menu_over(2,<%=pageType %>)">
                <img src="/Images/top_menu02<%= pageType==2?"on":"off" %>.jpg" alt="游戏下载" id="m2"
                    border="0" /></a></li>
            <li><a href="/Manage/FineryID.aspx" onmouseover="menu_over(3,<%=pageType %>)" onmouseout="menu_out(3,<%=pageType %>)"
                onfocus="menu_over(3,<%=pageType %>)">
                <img src="/Images/top_menu03<%= pageType==3?"on":"off" %>.jpg" alt="精品ID" id="m3"
                    border="0" /></a></li>
            <li><a href="/Manage/Pay/Default.aspx" onmouseover="menu_over(4,<%=pageType %>)"
                onmouseout="menu_out(4,<%=pageType %>)" onfocus="menu_over(4,<%=pageType %>)">
                <img src="/Images/top_menu04<%= pageType==4?"on":"off" %>.jpg" alt="账户充值" id="m4"
                    border="0" /></a></li>
            <li><a href="/NewsList.aspx" onmouseover="menu_over(5,<%=pageType %>)" onmouseout="menu_out(5,<%=pageType %>)"
                onfocus="menu_over(5,<%=pageType %>)">
                <img src="/Images/top_menu05<%= pageType==5?"on":"off" %>.jpg" alt="新闻中心" id="m5"
                    border="0" /></a></li>
            <li><a href="/Promoter.aspx" onmouseover="menu_over(6,<%=pageType %>)" onmouseout="menu_out(6,<%=pageType %>)"
                onfocus="menu_over(6,<%=pageType %>)">
                <img src="/Images/top_menu06<%= pageType==6?"on":"off" %>.jpg" alt="推广员" id="m6"
                    border="0" /></a></li>
            <li><a href="/RankMoney.aspx" onmouseover="menu_over(7,<%=pageType %>)" onmouseout="menu_out(7,<%=pageType %>)"
                onfocus="menu_over(7,<%=pageType %>)">
                <img src="/Images/top_menu07<%= pageType==7?"on":"off" %>.jpg" alt="排行榜" id="m7"
                    border="0" /></a></li>
            <li><a href="/JiangPin.aspx" onmouseover="menu_over(8,<%=pageType %>)" onmouseout="menu_out(8,<%=pageType %>)"
                onfocus="menu_over(8,<%=pageType %>)">
                <img src="/Images/top_menu08<%= pageType==8?"on":"off" %>.jpg" alt="兑奖中间" id="m8"
                    border="0" /></a></li>
            <li><a href="/Service.aspx" onmouseover="menu_over(9,<%=pageType %>)" onmouseout="menu_out(9,<%=pageType %>)"
                onfocus="menu_over(9,<%=pageType %>)">
                <img src="/Images/top_menu09<%= pageType==9?"on":"off" %>.jpg" alt="客服中心" id="m9"
                    border="0" /></a></li>
        </ul>
    </div>
    
    -->
</div>

<script type="text/javascript">
 
    var srcs = "<%=strSrc %>";
    var urls = "<%=strUrl %>";
   
    var srcsarray = srcs.split(',');
    var urlsarray = urls.split(',');
    var num = urlsarray.length-1;
    var nowpage = 1;
    var strgameContent = "";
    var pageCount = (num % 4 == 0) ? parseInt(num / 4) : parseInt(num / 4) + 1;
   
    first();
    
    function first() {
        var prec = (nowpage - 1) * 4;
        strgameContent = "";
        for (var i = prec + 1; i < prec + 5; i++) {
            if (i <= num) {

                strgameContent = strgameContent + "<li><a href='" + urlsarray[i - 1] + "'> <img src='" + srcsarray[i - 1] + "' alt='' border='0' width='70' height='70' /></a></li>";
            }

        }
       
        document.getElementById("gametop").innerHTML = strgameContent;
    }
    function nex() {
        
        if (pageCount > nowpage) {

            nowpage = nowpage + 1;
            var prec = (nowpage - 1) * 4;
            strgameContent = "";
            for (var i = prec+1; i < prec + 5; i++) {
                if (i <= num) {
                    
                    strgameContent = strgameContent + "<li><a href='" + urlsarray[i-1] + "'> <img src='"+srcsarray[i-1]+"' alt='' border='0' width='70' height='70' /></a></li>";
                }

            }
            document.getElementById("gametop").innerHTML = strgameContent;
            
          
        }

    }
    function pre() {
    
        if (nowpage > 1) {
            var prec = (nowpage - 2) * 4;
            strgameContent = "";
            for (var i = prec + 1; i < prec + 5; i++) {
                if (i <= num) {

                    strgameContent = strgameContent + "<li><a href='" + urlsarray[i - 1] + "'> <img src='" + srcsarray[i - 1] + "' alt='' border='0' width='70' height='70' /></a></li>";
                }

            }
            document.getElementById("gametop").innerHTML = strgameContent;
            nowpage = nowpage - 1;
           
        }
    } </script>

