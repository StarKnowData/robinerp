<%@ Page Title="" Language="C#" MasterPageFile="~/MasterPage.Master" AutoEventWireup="true" CodeBehind="AboutOrderSys.aspx.cs" Inherits="QPS.Web.AboutOrderSys" %>
<asp:Content ID="Content1" ContentPlaceHolderID="head" runat="server">
</asp:Content>
<asp:Content ID="Content2" ContentPlaceHolderID="ContentPlaceHolder1" runat="server">
    <div class="nymiddle">
 <div class="gywm" >
     <asp:Repeater ID="Repeater1" runat="server">
          <ItemTemplate>
             <%# Eval("DContent").ToString()%>
                  </ItemTemplate>
     </asp:Repeater>
</div>
</div>

</asp:Content>
