<%@ Page Title="" Language="C#" MasterPageFile="~/MasterPage.Master" AutoEventWireup="true" CodeBehind="Yxzx.aspx.cs" Inherits="QPS.Web.Yxzx" %>
<asp:Content ID="Content1" ContentPlaceHolderID="head" runat="server">
</asp:Content>
<asp:Content ID="Content2" ContentPlaceHolderID="ContentPlaceHolder1" runat="server">
    <div class="nymiddle">
 <div class="gywm" > 
   <asp:Repeater ID="RepeaterYx" runat="server">
          <ItemTemplate>
             <%# Eval("DContent").ToString()%>
                  </ItemTemplate>
     </asp:Repeater>
   </div>
</div>

</asp:Content>
