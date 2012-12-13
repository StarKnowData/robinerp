using System;
using System.Collections.Generic;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;

namespace QPS.Web.BusiMan
{
    public partial class Order : System.Web.UI.Page
    {
      static  int  orderid;
        protected void Page_Load(object sender, EventArgs e)
      {
              orderid =Convert.ToInt32(Request.QueryString["id"]);
              QPS.NEW.BLL.Orderform Border = new QPS.NEW.BLL.Orderform();
              QPS.NEW.Model.Orderform Morder = Border.GetModel(orderid);
              QPS.NEW.BLL.Users u = new QPS.NEW.BLL.Users();
              QPS.NEW.BLL.Room r = new QPS.NEW.BLL.Room();
              int roomid=(int)  Morder.Roomid;
              int userid =(int) Morder.Userid;
             txfRoomName.Value = r.GetModel(roomid).Name;
                 txfUserName.Value = u.GetModel(userid).Username;
             //txfBeverageCost.Text =Border.GetModel(orderid).Beveragecost.ToString();
              txfOrderId.Value = orderid.ToString();
        }

        protected void btnCreate_Click(object sender, EventArgs e)
        {
            try
            { //转换为整数
                int ID = Convert.ToInt32(orderid);
                QPS.NEW.BLL.Orderform Border = new QPS.NEW.BLL.Orderform();
                QPS.NEW.Model.Orderform order = Border.GetModel(ID);
                order.Beveragecost = Convert.ToDecimal(txfBeverageCost.Text);
                if (Border.Update(order))
                {
                    Response.Write("<script>alert('订单修改成功！')</script>");
                    Response.Write("<script>window.close()</script>");
                }
            }
            catch (Exception ex)
            {
                Response.Write("<script>alert('订单修改失败！')</script>");
            }
        }
    }
}
