using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;
using System.Data;
using System.Text;
namespace QPS.Web.UserMan
{
    public partial class OrderMan : System.Web.UI.Page
    {
        public DataTable Gettable(List<QPS.Model.Room> roomlist)
        {
            try
            {
                //创建DataTable
                DataTable dt = new DataTable();
                //创建新列
                DataColumn dc0 = dt.Columns.Add("棋牌室编号", typeof(int));
                DataColumn dc1 = dt.Columns.Add("棋牌室名称", typeof(string));
                DataColumn dc2 = dt.Columns.Add("棋牌室类型", typeof(string));
                DataColumn dc3 = dt.Columns.Add("价格", typeof(string));
                DataColumn dc4 = dt.Columns.Add("地区", typeof(string));
                DataColumn dc5 = dt.Columns.Add("地址", typeof(string));
                //DataColumn dc6 = dt.Columns.Add("退订", typeof(Button));
                foreach (QPS.Model.Room r in roomlist)
                {
                    DataRow dr = dt.NewRow();
                    dr[0] = r.Id;
                    dr[1] = r.Name;
                    dr[2] = r.RoomType;
                    dr[3] = r.RoomPrice;
                    dr[4] = r.Are;
                    dr[5] = r.Address;
                    //dr[6] = ht[i]["B_AuthorName"];

                    dt.Rows.Add(dr);
                }
                return dt;
            }
            catch (Exception ex)
            {
                throw ex;
            }
        }
        public void databind(GridView  gdv)
        {
            QPS.BLL.Users user = new QPS.BLL.Users();
            QPS.Model.Room Mroom = new QPS.Model.Room();
            QPS.BLL.Room Broom = new QPS.BLL.Room();
            QPS.BLL.Orderform Border = new QPS.BLL.Orderform();
            List<QPS.Model.Room> roomList = new List<QPS.Model.Room>();
            if (Session["username"] != null)
            {
                string uname = Session["username"].ToString();
                DataSet dsUser = user.GetList("Username='" + uname + "'");
                int uid = Convert.ToInt32(dsUser.Tables[0].Rows[0]["Id"]);
                List<QPS.Model.Orderform> orderlist = Border.GetModelList("Userid='" + uid + "'");
                foreach (QPS.Model.Orderform o in orderlist)
                {
                    int roomid = (int)o.Roomid;
                    roomList.Add(Broom.GetModel(roomid));
                }
            }
            gdv.DataSource = Gettable(roomList);
            gdv.DataBind();
        }
        protected void Page_Load(object sender, EventArgs e)
        {
            if (!IsPostBack)
            {
                databind(this.gdvPersonnalOrder);
            }
        }
        protected void gdvPersonnalOrder_RowDeleting(object sender, GridViewDeleteEventArgs e)
        {
           //得到单位编号
            string rowToDelete = gdvPersonnalOrder.DataKeys[e.RowIndex].Values[0].ToString();
          //转换为整数
           int ID=Convert.ToInt32(rowToDelete);
           QPS.BLL.Orderform Border = new QPS.BLL.Orderform();
           QPS.BLL.Room Broom = new QPS.BLL.Room();
  
           DataSet dsorder= Border.GetList("Roomid ='" + ID + "'");
           int Oid = Convert.ToInt32(dsorder.Tables[0].Rows[0]["Id"]);
           Border.Delete(Oid);
           QPS.Model.Room r = Broom.GetModel(ID);
           r.RoomState = 0;
           Broom.Update(r);
           databind(gdvPersonnalOrder);
        }
    }
}
