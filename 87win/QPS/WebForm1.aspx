 
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head id="Head1"><meta http-equiv="Content-Type" content="text/html; charset=utf-8"><title>
	www.87win.cn
</title><link href="/style/mainstyle.css" rel="stylesheet" type="text/css" />
 
    <script type="text/javascript" src="/Public/Js/Global.js"></script>
 
    <script type="text/javascript" src="/Public/Js/FlashPlayer.js"></script>
 
    <script type="text/javascript" src="/Public/Js/marquee.js"></script>
 
    <script type="text/javascript" src="/Public/Js/jquery.js"></script>
 
    <script type="text/jscript">
        $(document).ready(
		function() {
		    //新闻分栏鼠标经过
		    $("#in_news > div.in_newstitle > a:not(:last)").mouseover(function() {
		        $(this).parent().children().removeClass("n_current");
		        $(this).addClass("n_current");
		        $("#in_news > ul:visible").hide();
		        $("#in_news > ul").eq($(this).index()).show();
		    });
		    if ($("#photo_list > dl > dt > span").length > 9) {
		        var dl = document.getElementById('photo_list');
		        var dt = dl.getElementsByTagName('dt')[0];
		        var dd = dl.getElementsByTagName('dd')[0];
		        var speed = 1;
		        dd.innerHTML = dt.innerHTML;
		        var rolling = function() {
		            if (dl.scrollLeft == dd.offsetLeft) {
		                dl.scrollLeft = 0;
		            }
		            else {
		                dl.scrollLeft++;
		            }
		        }
		        var timer = setInterval(rolling, speed)//设置定时器  
		        dl.onmouseover = function() { clearInterval(timer) } //鼠标移到marquee上时，清除定时器，停止滚动  
		        dl.onmouseout = function() { timer = setInterval(rolling, speed) } //鼠标移开时重设定时器
		    }
 
		}
	);
    </script>
 
<meta name="Keywords" content="真钱棋牌,棋牌游戏,棋牌游戏平台,棋牌小游戏,斗地主,斗地主小游戏,德州扑克,斗地主3人"><meta name="Description" content="最专业棋牌游戏开发公司，棋牌游戏运营棋牌游戏平台下载最大棋牌游戏开发公司八棋羸泊众平台。"></head>
<body>
    <div id="wrap">
        <!--header-->
        
 
<div id="header">
    <div class="header_con">
 
        	<h1 class="logo">
 
            	<a href="#" title="">
 
                	<img src="/images/logo.jpg" alt="棋牌游戏"/>
 
                </a>
 
            </h1>
 
            <!-- <div class="top_phone">
 
            	<img src="/images/top_phone.jpg" alt="热线电话" /> 
 
            </div> -->
 
        </div>
 
    <div class="nav">
    	<div>
 
        	<div>
 
            	<ul>
 
                	<li></li>
 
                </ul>
 
            </div>
 
        </div>
 
      <ul>
        <li><a href="/Default.aspx" class="current">首 页</a></li>
           <li><a href="/Down.aspx" >游戏下载</a></li>
        <li><a href="/Manage/Pay/Default.aspx" >帐户充值</a></li>
        <li><a href="/Photo.aspx" >玩家靓照</a></li>
        <li><a href="/Manage/FineryID.aspx" >精品ID</a></li>
      
         <li><a href="/NewsList.aspx" >新闻中心</a></li>
       
        <li><a href="/Promoter.aspx" >推广员</a></li>
        <li><a href="/RankMoney.aspx" >排行榜</a></li>
        <li><a href="/JiangPin.aspx" >兑奖中心</a></li>
        <li class="last"><a href="/Service.aspx" >客服中心</a></li>
      </ul>
    </div>
</div>
<script type="text/javascript"> 
  //  LogSuccess();
    //显示登录成功后的面板
    function LogSuccess() {
        var urlData = '/Public/LogSuccess.aspx?tdate=' + getDataTime();
        var strReturn = AjaxCall(urlData);
        if (strReturn != '') {
            document.getElementById('spanLoginForm').innerHTML = strReturn;
        }
    }
</script>
        <!--content-->
        <div id="content">
            <div id="left1">
                
<div id="downLoad"> 
            	<a href="/Down.aspx" title="游戏下载" class="download_btn"></a> 
				<ul>
 
            		<li><a href="/download/八棋赢完整版.exe" >·完整版 </a></li>
 
            		<li><a href="/download/八棋赢简洁版.exe" >·精编版 </a></li> 
            	</ul> 
        	</div>
 
<ul class="shortcut_but">
 
 <li><a href="/Manage/Reg.aspx" title="用户注册"><img src="/images/Bn_usezc.jpg"  alt="用户注册"/></a></li> 
  
 <li id="webCutKey_loginId"> <a href="/Manage/Login.aspx" title="个人中心"> <img src="/images/Bn_userct.jpg" alt="个人中心"/></a></li> 
 
 <li id="webCutKey_liIsShowOne"><a href="/Manage/Pay/Default.aspx" title="在线充值"><img src="/images/Bn_zxcz.jpg"  alt="在线充值"/></a></li> 
 <li id="webCutKey_liIsShowTwo"><a href="/Daoju.aspx" title="游戏商城"><img src="/images/Bn_shoping.jpg"   alt="游戏商城"/></a></li> 
 <li id="webCutKey_liIsShowThree"><a href="/Manage/Lottery.aspx" title="幸运抽奖"><img src="/images/Bn_xycj.jpg" alt="幸运抽奖"/></a></li> 
 
</ul>
 
 
                
 <div class="clear"></div>
<div class="left_cont">  
 
        		<div class="left_cont_title1"></div>
 
         		<ul class="leftList">
                    
                    <li class="leftHelpList1" ><a href='/News2.aspx?id=36'>幸运抽奖活动规则</a></li>
                    
                    <li class="leftHelpList2" ><a href='/News2.aspx?id=18'>如何下载游戏大厅</a></li>
                    
                    <li class="leftHelpList3" ><a href='/News2.aspx?id=4'>如何注册成为会员？</a></li>
                    
                    <li class="leftHelpList4" ><a href='/News2.aspx?id=17'>如何安装游戏大厅</a></li>
                    
                    <li class="leftHelpList5" ><a href='/News2.aspx?id=38'>比赛须知</a></li>
                    
                    <li class="leftHelpList6" ><a href='/News2.aspx?id=35'>如何开始游戏</a></li>
                    
         		 
 
        		</ul>
 
        		<div class="left_cont_title2"></div>
 
         		<ul class="leftList">
                    
<li class="leftkefuList1" ><a href='/News2.aspx?id=21'>常见问题解答</a></li>
                    
<li class="leftkefuList2" ><a href='/News2.aspx?id=20'>服务条款</a></li>
                    
<li class="leftkefuList3" ><a href='/News2.aspx?id=34'>在线提问</a></li>
                    
<li class="leftkefuList4" ><a href='/News2.aspx?id=22'>家长监控工程</a></li>
                    
<li class="leftkefuList5" ><a href='/News2.aspx?id=19'>问题处理流程</a></li>
                     
        		</ul>
 
        	</div>
            </div>
            <div class="content_main">
                <div id="banner">
                    <object id="scriptmain" width="463" classid="clsid:D27CDB6E-AE6D-11cf-96B8-444553540000"
                        name="scriptmain" codebase="http://download.macromedia.com/pub/shockwave/cabs/
                flash/swflash.cab#version=6,0,29,0" height="201">
                        <param value="/images/Flash/Carousel.swf?bcastr_xml_url=/upload/xml/flash.xml&x=sldflsdf"
                            name="movie" />
                        <param value="high" name="quality" />
                        <param value="noscale" name="scale" />
                        <param value="false" name="LOOP" />
                        <param value="false" name="menu" />
                        <param value="transparent" name="wmode" />
                        <embed width="463" name="scriptmain" height="201" quality="high" salign="T" wmode="transparent"
                            pluginspage="http://www.macromedia.com/go/getflashplayer" src="/images/Flash/Carousel.swf?bcastr_xml_url=/upload/xml/flash.xml&x=sldl3sdf"
                            type="application/x-shockwave-flash" loop="false" menu="false"></embed>
                    </object>
                </div>
                <div class="leftTopD" style="margin-bottom: 10px;">
                    <div class="indwxNews">
                        <h3>
                            <a href="/NewsList.aspx">更多&gt;&gt;</a></h3>
                        <ul class="newsList">
                            
                                    <li><span>
                                        2012-10-20</span><a href='/News2.aspx?id=43'
                                            title='癞子斗地主比赛须知' style='color: #006699;'>癞子斗地主比赛须知</a></li>
                                
                                    <li><span>
                                        2012-10-16</span><a href='/News2.aspx?id=48'
                                            title='《八棋赢》关于抽奖奖品发放' style='color: #FF0000;'>《八棋赢》关于抽奖奖品发放</a></li>
                                
                                    <li><span>
                                        2012-10-13</span><a href='/News2.aspx?id=42'
                                            title='金币天天领' style='color: #006699;'>金币天天领</a></li>
                                
                                    <li><span>
                                        2012-09-28</span><a href='/News2.aspx?id=41'
                                            title='八棋赢给青春惊喜，换个角度做自己.' style='color: #006699;'>八棋赢给青春惊喜，换个角度做自己.</a></li>
                                
                                    <li><span>
                                        2012-09-27</span><a href='/News2.aspx?id=40'
                                            title='桃李满天下，恩情似海深' style='color: #006699;'>桃李满天下，恩情似海深</a></li>
                                
                                    <li><span>
                                        2012-09-27</span><a href='/News2.aspx?id=39'
                                            title='逢8必送，抢金币啦！' style='color: #006699;'>逢8必送，抢金币啦！</a></li>
                                
                        </ul>
                    </div>
                    <div class="newsBottom">
                    </div>
                </div>
                <div class="leftTopD" style="margin-bottom: 6px;">
                    <div class="indwxNews">
                        <h4>
                            <a href="/news2.aspx">更多&gt;&gt;</a></h4>
                        <ul class="newsList">
                            
                                    <li><span>
                                        2012-09-27</span><a href='/News2.aspx?id=33'
                                            title='如何送朋友金币' style='color: #006699;'>如何送朋友金币</a></li>
                                
                                    <li><span>
                                        2012-09-15</span><a href='/News2.aspx?id=23'
                                            title='银行不能存取' style='color: #006699;'>银行不能存取</a></li>
                                
                                    <li><span>
                                        2012-09-15</span><a href='/News2.aspx?id=25'
                                            title='怎么找回密码' style='color: #006699;'>怎么找回密码</a></li>
                                
                                    <li><span>
                                        2012-09-15</span><a href='/News2.aspx?id=26'
                                            title='金币可以换现金吗' style='color: #006699;'>金币可以换现金吗</a></li>
                                
                                    <li><span>
                                        2012-09-15</span><a href='/News2.aspx?id=31'
                                            title='银行里的金币怎么充到游戏账户里' style='color: #006699;'>银行里的金币怎么充到游戏账户里</a></li>
                                
                        </ul>
                    </div>
                    <div class="newsBottom">
                    </div>
                </div>
            </div>
        </div>
        <div class="content_right">
            
 
<div class="righttop">
 
        	<ul>
 
        		<li class="zxzx">
 
                <a href="tencent://message/?uin=2637416916&Site=八棋赢棋牌游戏&Menu=yes" title="在线咨询">
 
                <img src="/images/Bn_phone.jpg" />
 
                 </a>
 
                </li>   
 
         		<li class="QQ"><img src="/images/qq.jpg" />
 
                	<h2>114768805</h2>
 
                	<h2></h2>
 
                	<h2></h2>
 
                </li> 
 
         		<li class="telephone"><img src="/images/phone.jpg" />
 
                	<h1>400-0911-987</h1>
 
                </li> 
 
        	</ul> 
 
        </div> 
 
 
            <div class="gamelist">
                <div>
                    <h2 class="gameList1">
                    </h2>
                    <ul class="game_pl">
                        
                                <li><a href='/GameInfo3.aspx?id=10001300' title='欢乐斗地主'>
                                    <img src='/images/ico/10001300.jpg' alt='欢乐斗地主'>
                                    欢乐斗地主
                                </a></li>
                            
                                <li><a href='/GameInfo3.aspx?id=10003300' title='斗地主３人'>
                                    <img src='/images/ico/10003300.jpg' alt='斗地主３人'>
                                    斗地主３人
                                </a></li>
                            
                                <li><a href='/GameInfo3.aspx?id=10003400' title='癞子斗地主'>
                                    <img src='/images/ico/10003400.jpg' alt='癞子斗地主'>
                                    癞子斗地主
                                </a></li>
                            
                                <li><a href='/GameInfo3.aspx?id=10306600' title='扎金花６人'>
                                    <img src='/images/ico/10306600.jpg' alt='扎金花６人'>
                                    扎金花６人
                                </a></li>
                            
                                <li><a href='/GameInfo3.aspx?id=10900400' title='牛牛４人'>
                                    <img src='/images/ico/10900400.jpg' alt='牛牛４人'>
                                    牛牛４人
                                </a></li>
                            
                                <li><a href='/GameInfo3.aspx?id=11302800' title='德克萨斯扑克'>
                                    <img src='/images/ico/11302800.jpg' alt='德克萨斯扑克'>
                                    德克萨斯扑克
                                </a></li>
                            
                    </ul>
                    <h2 class="gameList5">
                    </h2>
                    <ul class="game_other">
                        
                    </ul>
                    <h2 class="gameList4">
                    </h2>
                    <ul class="game_other">
                        
                                <li><a href='/GameInfo3.aspx?id=30100200' title='中国象棋'>
                                    <img src='/images/ico/30100200.jpg' alt='中国象棋'>
                                    中国象棋
                                </a></li>
                            
                                <li><a href='/GameInfo3.aspx?id=30200200' title='中国围棋'>
                                    <img src='/images/ico/30200200.jpg' alt='中国围棋'>
                                    中国围棋
                                </a></li>
                            
                                <li><a href='/GameInfo3.aspx?id=30300400' title='四国军棋'>
                                    <img src='/images/ico/30300400.jpg' alt='四国军棋'>
                                    四国军棋
                                </a></li>
                            
                                <li><a href='/GameInfo3.aspx?id=30500400' title='飞行棋'>
                                    <img src='/images/ico/30500400.jpg' alt='飞行棋'>
                                    飞行棋
                                </a></li>
                            
                                <li><a href='/GameInfo3.aspx?id=30606600' title='连连看'>
                                    <img src='/images/ico/30606600.jpg' alt='连连看'>
                                    连连看
                                </a></li>
                            
                    </ul>
                </div>
            </div>
        </div>
        <div class="clear">
        </div>
        <!--right End-->
    </div>
    <!--content End-->
    
    <!--footer-->
    
 
 <div id="footer">
 
	<div class="footer_con">
 
    	<dl>
 
        	<dt>健康游戏忠告：</dt>
 
            <dd>抵制不良游戏</dd>                      
 
            <dd>拒绝盗版游戏</dd> 
 
            <dd>注意自我保护</dd> 
 
            <dd>谨防受骗上当</dd> 
 
            <dd>适度游戏益脑</dd> 
 
            <dd>沉迷游戏伤身</dd> 
 
            <dd>合理按排时间</dd> 	
 
            <dd>享受健康生活</dd> 	
 
        </dl> 
 
        <div class="footer_info">
 
 			<p>网站备案号：     版权所有 © 八棋赢棋牌游戏 </p>
 
            <p class="footer_ic">技术支持：深圳市正易龙科技有限公司</p>
 
    	</div>
 
    </div>
 
    
 
</div>
 
 
</body>
</html>

