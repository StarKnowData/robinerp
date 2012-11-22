<%@ Page Title="" Language="C#" MasterPageFile="~/MainMaser.Master" AutoEventWireup="true" CodeBehind="FeedBack.aspx.cs" Inherits="QPS.Web.FeedBack" %>
<asp:Content ID="Content1" ContentPlaceHolderID="head" runat="server">
    <title>意见反馈</title>
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
          <div class="yjtop"><div style="clear:both; overflow:hidden; height:0; font-size:1px; "></div></div>
          <div class="yjmid">
               <div class="titled">感谢阁下的关注，期待合作或得到您的宝贵意见和建议，我们将尽快联系您！</div>
               <div class="zcnra">
                    <ul>
                        <li><h3>姓名：</h3>
                            <asp:TextBox ID="txbname" runat="server" CssClass="zca1"></asp:TextBox></li>
                     <li><h3>标题：</h3>
                            <asp:TextBox ID="txtTitle" runat="server" CssClass="zca1" ></asp:TextBox>
                         </li>
                        <li><h3>内容：</h3>
                            <asp:TextBox ID="txbContent" class="zca2" MaxLength="1073741823" TextMode="MultiLine" orderWidth="0px" runat="server" ></asp:TextBox>
                         </li>
                  
                        <li>
                            <asp:Button ID="btnSubmit" runat="server" Text=""  class="zca3" 
                                onclick="btnSubmit_Click"/>

                        </li>
                    </ul>
            </div>
          </div>
          <div class="yjend"><div style="clear:both; overflow:hidden; height:0; font-size:1px; "></div></div>
     </div>
</div>
<!--mid]]-->
     <!--nymiddle]]-->
</asp:Content>
