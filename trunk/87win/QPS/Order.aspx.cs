using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;
using System.Text;
using System.Data;
namespace QPS.Web
{
    public partial class Order : System.Web.UI.Page
    {
        public DataSet ds;
        QPS.NEW.BLL.Room room = new QPS.NEW.BLL.Room();
        QPS.NEW.Model.Room mroom = new QPS.NEW.Model.Room();
        QPS.NEW.BLL.Orderform Border = new QPS.NEW.BLL.Orderform();
        QPS.NEW.Model.Orderform Morder = new QPS.NEW.Model.Orderform();
        QPS.NEW.BLL.Users user = new QPS.NEW.BLL.Users();
        static int roomid; static int userid;
        protected void Page_Load(object sender, EventArgs e)
        {
            if (!IsPostBack)
            {
                
                roomid = Int32.Parse(Request.QueryString["id"].Trim());
                StringBuilder sb = new StringBuilder();
                sb.Append("Id=");
                sb.Append(roomid);
                ds = room.GetList(sb.ToString());
                DataList1.DataSource = ds;
                DataList1.DataBind();
                if (Session["username"] != null)
                {
                    string uname = Session["username"].ToString();
                    txbOrderPersonInfo.Text = uname;
                    DataSet dsUser = user.GetList(uname);
                    if (dsUser.Tables[0].Rows[0]["Phone"].ToString() != "")
                    {
                        txbPhone.Text = dsUser.Tables[0].Rows[0]["Phone"].ToString();
                    }

                    userid = Convert.ToInt32(dsUser.Tables[0].Rows[0]["UserID"]);
                }
            }
        }
        protected void btnSub_Click(object sender, EventArgs e)
        {
            if (txbPhone.Text == "")
            {
                Response.Write("<script>alert('请填写手机号!')</script>");
                return;
            }
            string erromsg = string.Empty;
            string celpattern = @"(^18\d{9}$)|(^13\d{9}$)|(^15\d{9}$)";
            if (txbNum.Text == "")
            {
                Response.Write("<script>alert('请填写预定人数!')</script>");
                return;
            }
            string IsNumeric = @"^[0-9]+$";
            if (!System.Text.RegularExpressions.Regex.IsMatch(txbNum.Text, IsNumeric))
            {
                Response.Write("<script>alert('请填写数字!')</script>");
                return;
            }
            if (Calendar1.SelectedDate.ToString() == "" || Calendar2.SelectedDate.ToString() == "")
            {
                Response.Write("<script>alert('请填写预定预定时间!')</script>");
                return;
            }
            if (txbPhone.Text != "")
            {
                if (!System.Text.RegularExpressions.Regex.IsMatch(txbPhone.Text, celpattern))
                {
                    Response.Write("<script>alert('输入的手机号有错误,请重新输入!')</script>");
                    return;
                }
            }
            try
            {
                //生成一张订单 然后 修改房间信息表的房间状态  最后添加积分信息
                double starthour = Convert.ToDouble(this.dplStartTime.SelectedValue);
                DateTime ddd = this.Calendar1.SelectedDate;
                DateTime startdate = this.Calendar1.SelectedDate.AddHours(starthour);
                double endhour = Convert.ToDouble(this.dplEndTime.SelectedValue);
                DateTime enddate = this.Calendar2.SelectedDate.AddHours(endhour);
                if (startdate >= enddate)
                {
                    Response.Write("<script>alert('起始时间不应该早于结束时间，请认真填写预定时间')</script>");
                    return;
                }
                Morder.Roomid = roomid;
                Morder.Userid = userid;
                Morder.StartTime = startdate;
                Morder.endTime = enddate;
                Morder.OrderNumber = txbNum.Text.Trim();
                Border.Add(Morder);
                QPS.NEW.Model.Room r = room.GetModel(roomid);
                r.RoomState = 1;
                room.Update(r);
                QPS.NEW.BLL.Users Buser = new QPS.NEW.BLL.Users();
                QPS.NEW.Model.Users Muser = Buser.GetModel(userid);
                Muser.Phone = txbPhone.Text.Trim();
                Buser.Update(Muser);
                Response.Redirect("MainPage.aspx", false);
            }
            catch (Exception ex)
            {
                Response.Write("<script>alert('预定失败!')</script>");
                return;
            }
        }
    }
}
