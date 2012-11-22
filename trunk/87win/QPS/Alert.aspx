<%@ Page Title="" Language="C#" MasterPageFile="~/MainMaser.Master"AutoEventWireup="true" CodeBehind="Alert.aspx.cs" Inherits="QPS.Web.Alert" %>
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
