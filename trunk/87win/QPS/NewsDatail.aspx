<%@ Page Language="C#" MasterPageFile="~/MainMaser.Master" AutoEventWireup="true" CodeBehind="NewsDatail.aspx.cs" Inherits="QPS.Web.NewsDatail" Title="无标题页" %>
<asp:Content ID="Content1" ContentPlaceHolderID="head" runat="server">
</asp:Content>
<asp:Content ID="Content2" ContentPlaceHolderID="ContentPlaceHolder1" runat="server">
    <!--mid[[-->
<div class="mid">
     <div class="nyleft">
          <div class="ptxz">
               <a href="http://game.87win.cn/download/八棋赢简洁版.exe">&nbsp;</a>
          </div>
          <div class="lxfs">
               <span><a href="tencent://message/?uin=2637416916&Site=八棋赢棋牌游戏&Menu=yes">企业QQ<br/>在线客服</a></span>
          </div>
     </div>
     <div class="nyright">
          <div class="xbanner">
               <a href="#"><img src="images/xsimg7.jpg" alt="" /></a>
          </div>
          <div class="weizi"><a href="#">首页</a>><a href="#">新闻</a></div>
          <div class="dttop" style="margin-top:0;"><div style="clear:both; overflow:hidden; height:0; font-size:1px; "></div></div>
          <div class="dtmid">
               <div class="xwxx">
                   <asp:DataList ID="DataList1" runat="server">
                              <ItemTemplate>
                  <h3 ><%# Eval("Title").ToString()%></h3>
                  <h4>时间： <%# Eval("time").ToString()%>    </h4>
                      <ul> <%# Eval("Content").ToString()%> </ul> 
                  </ItemTemplate>
                   </asp:DataList>
               </div>
          </div>
          <div class="dtend"><div style="clear:both; overflow:hidden; height:0; font-size:1px; "></div></div>
     </div>
</div>
<!--mid]]-->
</asp:Content>
