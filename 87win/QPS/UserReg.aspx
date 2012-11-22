<%@ Page Title="" Language="C#" MasterPageFile="~/MainMaser.Master" AutoEventWireup="true" CodeBehind="UserReg.aspx.cs" Inherits="QPS.Web.UserReg" %>
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
          <div class="yjtop"><div style="clear:both; overflow:hidden; height:0; font-size:1px; "></div></div>
          <div class="yjmid">
               <div class="titled">欢迎注册成为八旗赢棋牌联盟用户</div>
               <div id="xzmenu">
                    <div id="Div1">
                 <asp:RadioButton ID="rbtuser" runat="server" Text="普通用户" GroupName="xzmenu" 
                     Checked="True"  />
                      <asp:RadioButton ID="rbtBusiuser" runat="server" Text="企业用户" 
                     GroupName="xzmenu"  />
               </div>
               </div>
               <div class="zcnra" id="cotant_1">
                    <ul>
                        <li><h3>用户名：</h3><input type="text" name="txtUser" id="txtUser" class="zca1" runat="server"/><p>*用户名由6-12位　字符　字母　数字构成</p></li>
                        <li><h3>密码：</h3><input type="password" name="txtPwd" id="txtPwd" class="zca1" runat="server" /><p>*密码由6-20位　英文　字母　或数字组成</p></li>
                        <li><h3>确认密码：</h3><input type="password" name="txtRePwd" id="txtRePwd" class="zca1" runat="server" /><p>*和上面密码相同</p></li>
                        <li><h3>昵称：</h3><input type="text" name="txtNickname" id="txtNickname" class="zca1" runat="server"/><p>*用户昵称由2-6位　汉字字构成</p></li>
                        <li><h4>完善信息：</h4></li>
                        <li><h3>手机号：</h3><input type="text" name="txtShouj" id="txtShouj" class="zca1" runat="server"/></li>
                        <li><h3>邮箱：</h3><input type="text" name="txtEm" id="txtEm" class="zca1" runat="server" /></li>
                        <li><h3>地址：</h3><input type="text" name="txtDz" id="txtDz" class="zca1" runat="server"/></li>
                        <li> <asp:Button ID="btn_Reg" CssClass="zca6" runat="server" Text="" 
                                onclick="btn_Reg_Click" />   
  <input type="checkbox" name="checkbox" id="checkbox" runat="server" class="zca7"/><h5>我已阅读并同意<a href="Alert.aspx">使用条款</a></h5>
                        </li>
                    </ul>
             </div>

          </div>
          <div class="yjend"><div style="clear:both; overflow:hidden; height:0; font-size:1px; "></div></div>
     </div>
</div>
<!--mid]]-->
</asp:Content>
