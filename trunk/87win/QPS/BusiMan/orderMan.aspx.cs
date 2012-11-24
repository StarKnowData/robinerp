using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;
using System.Data;
namespace QPS.Web.BusiMan
{
    public partial class orderMan : System.Web.UI.Page
    {
        public static string uname;
        public static int uid;
        public DataTable databind()
        {
          DataTable dt = new DataTable();

          QPS.NEW.BLL.Enterprise user = new QPS.NEW.BLL.Enterprise();
        QPS.NEW.BLL.Users u = new QPS.NEW.BLL.Users();
        QPS.NEW.BLL.Room BRoom = new QPS.NEW.BLL.Room();
        QPS.NEW.Model.Room Mroom = new QPS.NEW.Model.Room();
        QPS.NEW.BLL.Orderform Border = new QPS.NEW.BLL.Orderform();
        List<QPS.NEW.Model.Room> roomList = new List<QPS.NEW.Model.Room>();
        List<QPS.NEW.Model.Orderform> orderList = new List<QPS.NEW.Model.Orderform>();
        List<QPS.NEW.Model.Users> userList = new List<QPS.NEW.Model.Users>();
         DataColumn dc0 = dt.Columns.Add("订单编号", typeof(int));
        DataColumn dc1 = dt.Columns.Add("棋牌室名称", typeof(string));
        DataColumn dc2 = dt.Columns.Add("用户", typeof(string));
        DataColumn dc3 = dt.Columns.Add("酒水费", typeof(float));
        DataColumn dc4 = dt.Columns.Add("是否有效",typeof(string));
          dc0.ReadOnly = true;
        dc1.ReadOnly = true;
        dc2.ReadOnly = true;
       
         DataSet dsUser = user.GetList("Username='" + uname + "'");
              uid = Convert.ToInt32(dsUser.Tables[0].Rows[0]["Id"]);
                //获取RoomID
                DataSet dsRoom = BRoom.GetList("OwnerID='"+uid+"' ");
                for (int i = 0; i < dsRoom.Tables[0].Rows.Count; i++)
                {
                    int  roomid =Convert.ToInt32(dsRoom.Tables[0].Rows[i]["Id"]);
                    QPS.NEW.Model.Room r = BRoom.GetModel(roomid);
                    DataSet dsOrder = Border.GetList("Roomid='" + roomid + "' and IsDelete=0");
                    if (dsOrder.Tables[0].Rows.Count == 0)
                        continue;
                    for (int j = 0; j < dsOrder.Tables[0].Rows.Count; j++)
                    {   
                        DataRow dr = dt.NewRow();
                        dr[1] = r.Name;
                        //订单ID
                        int orderid = Convert.ToInt32(dsOrder.Tables[0].Rows[j]["Id"]);
                        dr[0] = orderid;
                        int userid = Convert.ToInt32(dsOrder.Tables[0].Rows[j]["Userid"]);
                        string username=  u.GetModel(userid).Username;
                        dr[2]=username;
                        dr[3] = dsOrder.Tables[0].Rows[j]["Beveragecost"]; 
                        dr[4]=dsOrder.Tables[0].Rows[j]["RoomType"];
                        dt.Rows.Add(dr);
                    }                  
        }
            return dt;
        }

        protected void Page_Load(object sender, EventArgs e)
        {
            if (!IsPostBack)
            {
                
                if (Session["username"] != null)
                {//获取Uid
                    uname = Session["username"].ToString();
                    gdvOrder.DataSource = databind();
                    gdvOrder.DataBind();
                }
            }
            }
        public string GetExamine(int startID)
        {
            string tempStart = string.Empty;
            switch (startID)
            {
                case 0:
                    tempStart = "无效";
                    break;
                case 1:
                    tempStart = "有效";
                    break;
                default:
                    tempStart = "未知";
                    break;
            }
            return tempStart;
        }

        protected void gdvOrder_RowCommand(object sender, GridViewCommandEventArgs e)
        {
            ////得到单位编号
            //string rowUpdate = this.gdvOrder.DataKeys[].Values[0].ToString();
            ////转换为整数
            //int ID = Convert.ToInt32(rowUpdate);
            //QPS.BLL.Orderform Border = new QPS.BLL.Orderform();
            //QPS.Model.Orderform Morder = new QPS.Model.Orderform();
            //Morder.Id = ID;
            //Morder.Beveragecost = (decimal)this.gdvOrder.DataKeys[e.RowIndex].Values[3];
            //Border.Update(Morder);
            //gdvOrder.DataSource = databind();
            //gdvOrder.DataBind();
            string strArgument = e.CommandArgument.ToString();
            if (e.CommandName == "IsValidate")
            {
                string[] Argument = strArgument.Split('|');
                string id = Argument[0].ToString();

                string type = Argument[1].ToString();
                int ok;
                if (type == "0")
                { 
                    ok = 1; 
                }
                else 
                {
                    ok = 0; 
                }

                QPS.NEW.BLL.Orderform Border = new QPS.NEW.BLL.Orderform();
                QPS.NEW.Model.Orderform order = Border.GetModel(Convert.ToInt32(id));
                Border.UpdateType(id,type);
                //订单有效 则加上积分  否则 如果存在积分 则删除
                QPS.NEW.BLL.Integral Bint = new QPS.NEW.BLL.Integral();
                QPS.NEW.Model.Integral Mint = new QPS.NEW.Model.Integral();
                     if (Bint.GetList("OrderId='" + id + "'").Tables[0].Rows.Count > 0)//删除已有积分
                    {
                        Bint.Delete(Convert.ToInt32(Bint.GetList("OrderId='" + id + "'").Tables[0].Rows[0]["Id"]));
                    }
                if (ok == 1)//有效
                {
                    QPS.NEW.BLL.Room Broom = new QPS.NEW.BLL.Room();
                    QPS.NEW.Model.Room r = Broom.GetModel(order.Roomid);
                        Mint.OrderId = Convert.ToInt32(id);
                        Mint.RoomId = order.Roomid;
                        Mint.UserID = order.Userid.ToString();
                        Mint.CreateTime = order.StartTime;
                        TimeSpan ts = (TimeSpan)(order.endTime - order.StartTime);
                        Mint.Content = Convert.ToInt32((ts.Hours * (double)r.RoomPrice));
                        if (order.Beveragecost != null)
                        { Mint.Content += (int)order.Beveragecost; }
                        Bint.Add(Mint);
                    }
                }
                gdvOrder.DataSource = databind();
                gdvOrder.DataBind();
            }
        

        protected void gdvOrder_RowDeleting(object sender, GridViewDeleteEventArgs e)
        {
            //得到单位编号
            string rowToDelete = this.gdvOrder.DataKeys[e.RowIndex].Values[0].ToString();
            //转换为整数
            int ID = Convert.ToInt32(rowToDelete);
            QPS.NEW.BLL.Orderform Border = new QPS.NEW.BLL.Orderform();
            QPS.NEW.Model.Orderform morder = Border.GetModel(ID);
            morder.IsDelete = 1;
            Border.Update(morder);
            gdvOrder.DataSource= databind();
            gdvOrder.DataBind();
        }

        protected void gdvOrder_RowUpdating(object sender, GridViewUpdateEventArgs e)
        {
            //得到单位编号
            string rowUpdate = this.gdvOrder.DataKeys[e.RowIndex].Values[0].ToString();
            Response.Write("<script> window.open('Order.aspx?id="+rowUpdate+"', 'newwindow', 'height=600, width=850, toolbar=no, menubar=no, scrollbars=no, resizable=no, location=no, status=no');</script>");
          
        }
        
        protected void gdvOrder_RowEditing(object sender, GridViewEditEventArgs e)
        {
            ////得到单位编号
            //string rowUpdate = this.gdvOrder.DataKeys[e.NewEditIndex].Values[0].ToString();
            ////转换为整数
            //int ID = Convert.ToInt32(rowUpdate);
            //QPS.BLL.Orderform Border = new QPS.BLL.Orderform();
            //QPS.Model.Orderform Morder = new QPS.Model.Orderform();
            //Morder.Id = ID;
            //Morder.Beveragecost = (decimal)this.gdvOrder.DataKeys[e.NewEditIndex].Values[3];
            //Border.Update(Morder);
            //gdvOrder.DataSource = databind();
            //gdvOrder.DataBind();
        }
        }
    }

