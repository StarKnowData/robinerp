<%@ Page Title="" Language="C#" MasterPageFile="~/BusiMan/EnterMaster.Master" AutoEventWireup="true" CodeBehind="PersonnalInfo.aspx.cs" Inherits="QPS.Web.BusiMan.PersonnalInfo" %>
<asp:Content ID="Content1" ContentPlaceHolderID="head" runat="server">   <link href="css/gruser.css"  rel="stylesheet" type="text/css" />
</asp:Content>
<asp:Content ID="Content2" ContentPlaceHolderID="ContentPlaceHolder1" runat="server">

  <!--grright[[-->
          <div class="grright">
               <div class="grtitlea">
                    <span>信息管理</span>
               </div>
               <!--grbox[[-->
               <div class="grbox">
                    <div class="grxxa">
                    <ul>
                        <li><h3>用户名：</h3><input type="text" name="txfUserName" id="txfUserName" class="cja1" runat="server" />&nbsp; </li>
                        <li><h3>手机号：</h3><input type="text" name="txfPhone" id="txfPhone" class="cja1" runat="server" /></li>
                        <li><h3>昵称 ：</h3><input type="text" name="txfNickName" id="txfNickName" class="cja1" runat="server" /></li>
                        <li><h3>地址：</h3><input type="text" name="txfAddress" id="txfAddress" class="cja1" runat="server" /></li>
                             <li><h3>邮箱地址：</h3><input type="text" name="txfEmail" id="txfEmail" class="cja1" runat="server" /></li>
                        <li><asp:Button ID="btnModify" runat="server" Text="" cssClass="cja2" 
                                onclick="btnModify_Click" /></li>
                    </ul>
               </div>
               <!--grbox]]-->
          </div>
          <!--grright]]-->
     </div>
</asp:Content>
