using System;
using System.Collections.Generic;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;
using System.Data;
using System.Text;

namespace QPS.Web
{
    public partial class RoomDetail : System.Web.UI.Page
    {
        public DataSet ds;
        QPS.NEW.BLL.Room room = new QPS.NEW.BLL.Room();
        QPS.NEW.BLL.Poster poster = new QPS.NEW.BLL.Poster();
        protected void Page_Load(object sender, EventArgs e)
        {
            if (!IsPostBack)
            {
                int id = Int32.Parse(Request.QueryString["id"].Trim());
                StringBuilder sb = new StringBuilder();
                sb.Append("Id=");
                sb.Append(id);
                ds = room.GetList(sb.ToString());
                DataList2.DataSource = ds;
                DataList2.DataBind();
                DataList1.DataSource = ds;
                DataList1.DataBind();

                string roomAddress =
                    ds.Tables[0].Rows[0]["Are"].ToString() + " " + ds.Tables[0].Rows[0]["Address"].ToString();

                Page.ClientScript.RegisterStartupScript(
                    ClientScript.GetType(),
                    "",
                    "<script>searchRoomAddress('"+roomAddress+"');</script>"
                );
                
            
            }
        }


        protected void DataList1_ItemCommand(object source, DataListCommandEventArgs e)
        {
            if (e.CommandName == "Order")
            {
                if (Session["username"] == null)
                {
                    Response.Write("<script>alert('请先登录,预定失败！')</script>");
                    return;
                }
                string temp = e.CommandArgument.ToString();
                StringBuilder sb = new StringBuilder();
                sb.Append("Order.aspx?id=");
                sb.Append(temp);
                Response.Redirect(sb.ToString());
            }
        }
        protected void dlrecommand_ItemCommand(object source, DataListCommandEventArgs e)
        {

            if (e.CommandName == "ShowDetail")
            {
                string temp = e.CommandArgument.ToString();
                StringBuilder sb = new StringBuilder();
                sb.Append("Detail.aspx?id=");
                sb.Append(temp);
                Response.Redirect(sb.ToString());
            }
        }
    }
}
