using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;
using System.Data;
namespace QPS.Web.BusiMan
{
    public partial class ScoreMan : System.Web.UI.Page
    {
        protected void Page_Load(object sender, EventArgs e)
        {
            this.gdvScore.DataSource = Gettable();
            gdvScore.DataBind();
        } 
    
        public DataTable  Gettable()
        {   
            DataTable dt = new DataTable();
            QPS.NEW.BLL.Enterprise user = new QPS.NEW.BLL.Enterprise();
            QPS.NEW.BLL.Users u = new QPS.NEW.BLL.Users();
            QPS.NEW.Model.Room Mroom = new QPS.NEW.Model.Room();
            QPS.NEW.BLL.Room Broom = new QPS.NEW.BLL.Room();
            QPS.NEW.BLL.Orderform Border = new QPS.NEW.BLL.Orderform();
            QPS.NEW.BLL.Integral Bint = new QPS.NEW.BLL.Integral();
            List<QPS.Model.Room> roomList = new List<QPS.Model.Room>();
            List<QPS.Model.Orderform> orderlist = new List<QPS.Model.Orderform>();
            //创建新列

            DataColumn dc0 = dt.Columns.Add("积分编号", typeof(int));
            DataColumn dc1 = dt.Columns.Add("用户名称", typeof(string));
            DataColumn dc2 = dt.Columns.Add("棋牌室名称", typeof(string));
            DataColumn dc3 = dt.Columns.Add("积分", typeof(string));
            DataColumn dc4 = dt.Columns.Add("消费时间", typeof(string));
            if (Session["username"] != null)
            {
                //获取Uid
                string uname = Session["username"].ToString();
                DataSet dsUser = user.GetList("Username='" + uname + "'");
                int uid = Convert.ToInt32(dsUser.Tables[0].Rows[0]["Id"]);
                //获取RoomId
                DataSet dsRoom = Broom.GetList("OwnerID='" + uid + "'");
                //获取integratid
                for (int i = 0; i < dsRoom.Tables[0].Rows.Count; i++)
                {
                    int roomid =Convert.ToInt32( dsRoom.Tables[0].Rows[i]["Id"]);
                    DataSet dsInt = Bint.GetList("RoomId ='"+roomid+"'");
                    //获取Intid
                    for (int j = 0; j < dsInt.Tables[0].Rows.Count; j++)
                    {
                        DataRow dr = dt.NewRow();
                        int intId =Convert.ToInt32( dsInt.Tables[0].Rows[j]["Id"]);
                        int userid = Convert.ToInt32(Bint.GetModel(intId).UserID);
                        int orId=Convert.ToInt32(Bint.GetModel(intId).OrderId);
                        int rId = Convert.ToInt32(Bint.GetModel(intId).RoomId);
                        dr[0] = intId;
                        dr[2] = Broom.GetModel(rId).Name;
                        dr[1] = u.GetModel(userid).Username;
                        QPS.NEW.Model.Orderform order = Border.GetModel(orId);
                        DateTime starttime, endtime;
                        starttime = (DateTime)order.StartTime;
                        endtime = (DateTime)order.endTime;
                        float beCost =Convert.ToInt32(order.Beveragecost);
                        TimeSpan ts = endtime - starttime;
                     
                        int cost=Convert.ToInt32(ts.Hours * (double)Broom.GetModel(roomid).RoomPrice + beCost);
                        dr[3] =cost;
                        dr[4]=order.StartTime;
                        QPS.NEW.Model.Integral mint = Bint.GetModel(intId);
                        mint.Content=cost;
                        Bint.Update(mint);
                        dt.Rows.Add(dr);
                    }
                }
           }
                    return dt;
        }

        //protected void gdvRoom_RowDeleting(object sender, GridViewDeleteEventArgs e)
        //{
        //    //得到单位编号
  
        //    string rowToDelete = this.gdvScore.DataKeys[e.RowIndex].Values[0].ToString();
        //    int ID = Convert.ToInt32(rowToDelete);
        //    QPS.BLL.Integral Bint = new QPS.BLL.Integral();
        //    Bint.Delete(ID);
        //    this.gdvScore.DataSource = Gettable();
        //    gdvScore.DataBind();
        //}
    }
}

