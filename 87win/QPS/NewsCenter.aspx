<%@ Page Title="" Language="C#" MasterPageFile="~/MainMaser.Master" AutoEventWireup="true" CodeBehind="NewsCenter.aspx.cs" Inherits="QPS.Web.NewsCenter" %>
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
               <span><a href="tencent://message/?uin=2637416916&Site=八棋赢棋牌游戏&Menu=yes
">企业 QQ<br/>在线客服</a></span>
          </div>
     </div>
     <div class="nyright">
          <div class="xbanner">
               <a href="#"><img src="images/xsimg7.jpg" alt=""></a>
          </div>
          <div class="dttop"><div style="clear:both; overflow:hidden; height:0; font-size:1px; "></div></div>
          <div class="dtmid">
               <div class="titlec">最新动态</div>
                          <asp:DataList ID="Dlrecommand" runat="server" 
                                onitemcommand="dlrecommand_ItemCommand">
                            <ItemTemplate>  
                            <div class="dtlist">
                       <h3><asp:LinkButton ID="lbtRecommand" runat="server" CommandArgument=' <%#Eval("Id")%>' CommandName="ShowDetail"><%# Eval("Title").ToString()%></asp:LinkButton></h3>
                       <h4><%# Eval("time").ToString()%></h4></div>
                            </ItemTemplate>
                            </asp:DataList>
          </div> 
          <div class="dtend"><div style="clear:both; overflow:hidden; height:0; font-size:1px; "></div></div>
          </div>
 <!--mid]]-->
</asp:Content>
