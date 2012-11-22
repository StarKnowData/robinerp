<%@ Page Title="" Language="C#" MasterPageFile="~/BusiMan/EnterMaster.Master" AutoEventWireup="true" CodeBehind="ModPwd.aspx.cs" Inherits="QPS.Web.BusiMan.ModPwd" %>
<asp:Content ID="Content1" ContentPlaceHolderID="head" runat="server">
   <link href="css/gruser.css"  rel="stylesheet" type="text/css" />
</asp:Content>
<asp:Content ID="Content2" ContentPlaceHolderID="ContentPlaceHolder1" runat="server">
    <div class="grright">
               <div class="grtitlea">
                    <span>修改密码</span>
               </div>
               <!--grbox[[-->
               <div class="grbox">
                    <div class="grxxa">
                    <ul>
                     <li><h3>原始密码：</h3><input type="text" name="txfOriginalPwd" id="txfOriginalPwd" runat="server"  class="cja1"/></li>
                        <li><h3>修改密码：</h3><input type="password" name="txfModPwd" id="txfModPwd" class="cja1" runat="server" /></li>
                        <li><h3>再次确认：</h3><input type="password" name="txfRepwd" id="txfRepwd" class="cja1" runat="server" /></li>
                        <li>
                            <asp:Button ID="btnModPwd" runat="server" Text="" cssClass="cja5" 
                                onclick="btnModPwd_Click"/></li>
                    </ul>
               </div>
               </div>
               <!--grbox]]-->
          </div>
</asp:Content>
