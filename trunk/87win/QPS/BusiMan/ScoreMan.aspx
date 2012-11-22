<%@ Page Title="" Language="C#" MasterPageFile="~/BusiMan/EnterMaster.Master" AutoEventWireup="true" CodeBehind="ScoreMan.aspx.cs" Inherits="QPS.Web.BusiMan.ScoreMan" %>
<asp:Content ID="Content1" ContentPlaceHolderID="head" runat="server">
   <link href="css/gruser.css"  rel="stylesheet" type="text/css" />
</asp:Content>
<asp:Content ID="Content2" ContentPlaceHolderID="ContentPlaceHolder1" runat="server">

       <div class="grright">
              <div class="grtitlea">
                    <span>积分管理</span>
             </div>
              <div class="grbox">
                    <asp:GridView ID="gdvScore" runat="server" CellPadding="4" 
                       ForeColor="#333333" GridLines="None"  Width="100%"
                               DataKeyNames="积分编号" 
                        HorizontalAlign="Center">
                       <RowStyle BackColor="#EFF3FB" />  　 
                              <FooterStyle BackColor="#507CD1" Font-Bold="True" ForeColor="White" />
                        <PagerStyle BackColor="#2461BF" ForeColor="White" HorizontalAlign="Center" />
                        <SelectedRowStyle BackColor="#D1DDF1" Font-Bold="True" ForeColor="#333333" />
                        <HeaderStyle BackColor="#FE6A6A" Font-Bold="True" ForeColor="White" />
                        <EditRowStyle BackColor="#2461BF" />
                        <AlternatingRowStyle BackColor="White" />
    </asp:GridView></div> </div></asp:Content>
