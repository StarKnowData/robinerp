<%@ Page Language="C#" AutoEventWireup="true" CodeBehind="index.aspx.cs" Inherits="QPS.Web.index1" %>

<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">

<html xmlns="http://www.w3.org/1999/xhtml" >
<head runat="server">
    <title>首页</title>  
    <link href="css/index.css" rel="stylesheet" type="text/css">
</link>
</head>

<body>
<!--box[[-->
<div class="box">
     <!--header[[-->
     <div class="header">
          <img src="images/img1.jpg" alt="">
          <ul>
              <li><span><a href="#">设为首页</a>|<a href="#">加入收藏</a>|<a href="#">联系我们</a></span></li>
              <li><input name="textfield" type="text" class="texta1" id="textfield" value="请输入地址或名称" />
              <input type="submit" name="button" id="button" value="" class="texta2"/>
              </li>
          </ul>
     </div>
     <!--header]]-->
     <div class="nav">
          <ul>
              <li class="on"><a href="#">今日推荐</a></li>
              <li><a href="#">棋牌室预订</a></li>
              <li><a href="#">茶吧预约</a></li>
              <li><a href="#">在线客服</a></li>
          </ul>
     </div>
     <!--middle[[-->
     <div class="middle">
          <div class="diqu">
               <span>地区：<a href="#">江岸区(476)</a><a href="#">武昌区(557)</a><a href="#">江汉区(628)</a><a href="#">硚口区(160)</a><a href="#">汉阳区(162)</a><a href="#">洪山区(972)</a><a href="#">青山区(82)</a><a href="#">东西湖区(26)</a><a href="#">蔡甸区(15)</a><a href="#">江夏区(15)</a><a href="#">黄陂区(8)</a></span>
               <p>价格：<a href="#">20-50</a><a href="#">50-100</a><a href="#">100-200</a><a href="#">200-3008)</a></p>
               <ul><h3>排序：</h3><h4><a href="#">默认</a></h4><h5><a href="#">热门</a></h5><h6><a href="#">折扣</a></h6><h6><a href="#">价格</a></h6></ul>
          </div>
          <!--qpbox[[-->
          <div class="qpbox">
<%--                         <div class="qplist">
                    <div class="qpnra">
                         <a href="#"><img src="images/img2.jpg"></a>
                         <h3><a href="#">聚雅客棋牌室</a></h3><div style="clear:both; overflow:hidden; height:0; font-size:1px"></div>
                         <h4>老板为人豪爽，喜欢结交朋友，服务一流!可以按小时或圈结帐，斗地主等各类游戏齐全！还有免费晚餐，停车很方便，最重要的是24小时营业，亲朋好友聚会的好地方！</h4>
                    </div>
                    <div class="qpjg">
                         <ul>
                             <h3><a href="#">现价¥68</a></h3>
                             <h4>原价¥222　折扣3.1折 </h4>
                         </ul>
                         <a href="#"><img src="images/img5.jpg" alt=""></a>
                    </div>
               </div>--%>
               <div class="qplist">
                    <div class="qpnra">
                         <a href="#"><img src="images/img2.jpg"></a>
                         <h3><a href="#">聚雅客棋牌室</a></h3><div style="clear:both; overflow:hidden; height:0; font-size:1px"></div>
                         <h4>老板为人豪爽，喜欢结交朋友，服务一流!可以按小时或圈结帐，斗地主等各类游戏齐全！还有免费晚餐，停车很方便，最重要的是24小时营业，亲朋好友聚会的好地方！</h4>
                    </div>
                    <div class="qpjg">
                         <ul>
                             <h3><a href="#">现价¥68</a></h3>
                             <h4>原价¥222　折扣3.1折 </h4>
                         </ul>
                         <a href="#"><img src="images/img5.jpg" alt=""></a>
                    </div>
               </div>
               <div class="qplist">
                    <div class="qpnra">
                         <a href="#"><img src="images/img3.jpg"></a>
                         <h3><a href="#">聚雅客棋牌室</a></h3><div style="clear:both; overflow:hidden; height:0; font-size:1px"></div>
                         <h4>老板为人豪爽，喜欢结交朋友，服务一流!可以按小时或圈结帐，斗地主等各类游戏齐全！还有免费晚餐，停车很方便，最重要的是24小时营业，亲朋好友聚会的好地方！</h4>
                    </div>
                    <div class="qpjg">
                         <ul>
                             <h3><a href="#">现价¥68</a></h3>
                             <h4>原价¥222　折扣3.1折 </h4>
                         </ul>
                         <a href="#"><img src="images/img5.jpg" alt=""></a>
                    </div>
               </div>
               <div class="qplist">
                    <div class="qpnra">
                         <a href="#"><img src="images/img4.jpg"></a>
                         <h3><a href="#">聚雅客棋牌室</a></h3><div style="clear:both; overflow:hidden; height:0; font-size:1px"></div>
                         <h4>老板为人豪爽，喜欢结交朋友，服务一流!可以按小时或圈结帐，斗地主等各类游戏齐全！还有免费晚餐，停车很方便，最重要的是24小时营业，亲朋好友聚会的好地方！</h4>
                    </div>
                    <div class="qpjg">
                         <ul>
                             <h3><a href="#">现价¥68</a></h3>
                             <h4>原价¥222　折扣3.1折 </h4>
                         </ul>
                         <a href="#"><img src="images/img5.jpg" alt=""></a>
                    </div>
               </div>
               <div class="qplist">
                    <div class="qpnra">
                         <a href="#"><img src="images/img3.jpg"></a>
                         <h3><a href="#">聚雅客棋牌室</a></h3><div style="clear:both; overflow:hidden; height:0; font-size:1px"></div>
                         <h4>老板为人豪爽，喜欢结交朋友，服务一流!可以按小时或圈结帐，斗地主等各类游戏齐全！还有免费晚餐，停车很方便，最重要的是24小时营业，亲朋好友聚会的好地方！</h4>
                    </div>
                    <div class="qpjg">
                         <ul>
                             <h3><a href="#">现价¥68</a></h3>
                             <h4>原价¥222　折扣3.1折 </h4>
                         </ul>
                         <a href="#"><img src="images/img5.jpg" alt=""></a>
                    </div>
               </div>
               <div class="qplist">
                    <div class="qpnra">
                         <a href="#"><img src="images/img4.jpg"></a>
                         <h3><a href="#">聚雅客棋牌室</a></h3><div style="clear:both; overflow:hidden; height:0; font-size:1px"></div>
                         <h4>老板为人豪爽，喜欢结交朋友，服务一流!可以按小时或圈结帐，斗地主等各类游戏齐全！还有免费晚餐，停车很方便，最重要的是24小时营业，亲朋好友聚会的好地方！</h4>
                    </div>
                    <div class="qpjg">
                         <ul>
                             <h3><a href="#">现价¥68</a></h3>
                             <h4>原价¥222　折扣3.1折 </h4>
                         </ul>
                         <a href="#"><img src="images/img5.jpg" alt=""></a>
                    </div>
               </div>
               <div class="qplist">
                    <div class="qpnra">
                         <a href="#"><img src="images/img2.jpg"></a>
                         <h3><a href="#">聚雅客棋牌室</a></h3><div style="clear:both; overflow:hidden; height:0; font-size:1px"></div>
                         <h4>老板为人豪爽，喜欢结交朋友，服务一流!可以按小时或圈结帐，斗地主等各类游戏齐全！还有免费晚餐，停车很方便，最重要的是24小时营业，亲朋好友聚会的好地方！</h4>
                    </div>
                    <div class="qpjg">
                         <ul>
                             <h3><a href="#">现价¥68</a></h3>
                             <h4>原价¥222　折扣3.1折 </h4>
                         </ul>
                         <a href="#"><img src="images/img5.jpg" alt=""></a>
                    </div>
               </div>
               <div class="qplist">
                    <div class="qpnra">
                         <a href="#"><img src="images/img4.jpg"></a>
                         <h3><a href="#">聚雅客棋牌室</a></h3><div style="clear:both; overflow:hidden; height:0; font-size:1px"></div>
                         <h4>老板为人豪爽，喜欢结交朋友，服务一流!可以按小时或圈结帐，斗地主等各类游戏齐全！还有免费晚餐，停车很方便，最重要的是24小时营业，亲朋好友聚会的好地方！</h4>
                    </div>
                    <div class="qpjg">
                         <ul>
                             <h3><a href="#">现价¥68</a></h3>
                             <h4>原价¥222　折扣3.1折 </h4>
                         </ul>
                         <a href="#"><img src="images/img5.jpg" alt=""></a>
                    </div>
               </div>
               <div class="qplist">
                    <div class="qpnra">
                         <a href="#"><img src="images/img3.jpg"></a>
                         <h3><a href="#">聚雅客棋牌室</a></h3><div style="clear:both; overflow:hidden; height:0; font-size:1px"></div>
                         <h4>老板为人豪爽，喜欢结交朋友，服务一流!可以按小时或圈结帐，斗地主等各类游戏齐全！还有免费晚餐，停车很方便，最重要的是24小时营业，亲朋好友聚会的好地方！</h4>
                    </div>
                    <div class="qpjg">
                         <ul>
                             <h3><a href="#">现价¥68</a></h3>
                             <h4>原价¥222　折扣3.1折 </h4>
                         </ul>
                         <a href="#"><img src="images/img5.jpg" alt=""></a>
                    </div>
               </div>
               <div class="qplist">
                    <div class="qpnra">
                         <a href="#"><img src="images/img2.jpg"></a>
                         <h3><a href="#">聚雅客棋牌室</a></h3><div style="clear:both; overflow:hidden; height:0; font-size:1px"></div>
                         <h4>老板为人豪爽，喜欢结交朋友，服务一流!可以按小时或圈结帐，斗地主等各类游戏齐全！还有免费晚餐，停车很方便，最重要的是24小时营业，亲朋好友聚会的好地方！</h4>
                    </div>
                    <div class="qpjg">
                         <ul>
                             <h3><a href="#">现价¥68</a></h3>
                             <h4>原价¥222　折扣3.1折 </h4>
                         </ul>
                         <a href="#"><img src="images/img5.jpg" alt=""></a>
                    </div>
               </div>
          </div>
          <!--qpbox]]-->
          <div class="page">
               <a href="#" class="m">1</a><a href="#">2</a><a href="#">3</a><a href="#">4</a><a href="#">5</a><a href="#">6</a><a href="#" class="n">下一页</a>
          </div>
     </div>
     <!--middle]]-->
     <!--footer[[-->
     <div class="footer">
          <a href="#">关于我们</a><strong>|</strong><a href="#">意见反馈</a><strong>|</strong><a href="#">免责声明</a>Copyright © 2012 bqyqpslm.com.　All Rights Reserved.　鄂ICP证050897号
     </div><div style="clear:both; overflow:hidden; height:0; font-size:1px"></div>
     <!--footer]]-->
</div>
<!--box]]-->
</body>
</html>
