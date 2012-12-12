<%@ Page Title="" Language="C#" MasterPageFile="~/MainMaser.Master" AutoEventWireup="true"
    CodeBehind="UserLogin.aspx.cs" Inherits="QPS.Web.UserLogin" %>

<asp:Content ID="Content1" ContentPlaceHolderID="head" runat="server">
</asp:Content>
<asp:Content ID="Content2" ContentPlaceHolderID="ContentPlaceHolder1" runat="server">
    <div class="mid">
        <div class="nyleft">
            <div class="ptxz">
                <a href="http://game.87win.cn/download/八棋赢简洁版.exe">&nbsp;</a>
            </div>
            <div class="lxfs">
                <h3>
                    <a href="tencent://message/?uin=2637416916&Site=八棋赢棋牌游戏&Menu=yes">企业QQ<br />
                        在线客服</a></h3>
            </div>
        </div>
        <div class="nyright">
            <div class="yjtop">
                <div style="clear: both; overflow: hidden; height: 0; font-size: 1px;">
                </div>
            </div>
            <div class="yjmid">
                <div class="titled">
                    欢迎注册成为八旗赢棋牌联盟用户</div>
                <div id="xzmenu">
                    <asp:RadioButton ID="rbtuser" runat="server" Text="普通用户" GroupName="xzmenu" Checked="True" />
                    <asp:RadioButton ID="rbtBusiuser" runat="server" Text="企业用户" GroupName="xzmenu" />
                </div>
                <div class="zcb">
                    <div class="dla" id="cotant_1">
                        <ul>
                            <li>
                                <h3>
                                    用户名：</h3>
                                <asp:TextBox ID="txbUserName" runat="server" CssClass="zca1" Text=""></asp:TextBox></li>
                            <li>
                                <h3>
                                    密码：</h3>
                                <asp:TextBox ID="txbPwd" runat="server" CssClass="zca1" TextMode="Password" Text=""></asp:TextBox></li>
                            <li>
                                <h3>
                                    验证码：</h3>
                                <asp:TextBox ID="txbCode" runat="server" CssClass="zca1"></asp:TextBox>
                                <img id="imgCode" alt="看不清，请点击我！" src="checkcode.aspx" style="cursor: hand; width: 76px;
                                    height: 21px; margin-top: 20px;" onclick="this.src=this.src+'?'" /></li>
                            <li>
                                <asp:Button ID="btnLogin" runat="server" Text="" class="zca5" OnClick="btnLogin_Click" />
                            </li>
                        </ul>
                    </div>
                    <div class="zcnrb">
                        <span>还没有八棋赢棋牌室联盟账号？</span> <a href="UserReg.aspx">
                            <img src="images/nyimg8.jpg"></a>
                    </div>
                </div>
            </div>
            <div class="yjend">
                <div style="clear: both; overflow: hidden; height: 0; font-size: 1px;">
                </div>
            </div>
        </div>
    </div>
</asp:Content>
