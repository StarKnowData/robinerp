using System;
using System.Collections.Generic;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;
using System.Data;
using System.Text;
namespace QPS.Web.BusiMan
{
    public partial class RoomMan : System.Web.UI.Page
    {
        public DataTable Gettable(List<QPS.NEW.Model.Room> roomlist)
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
                //DataColumn dc6 = dt.Columns.Add("棋牌室状态", typeof(string));
                //DataColumn dc6 = dt.Columns.Add("退订", typeof(Button));
                foreach (QPS.NEW.Model.Room r in roomlist)
                {
                    DataRow dr = dt.NewRow();
                    dr[0] = r.Id;

                    dr[1] = r.Name;
                    dr[2] = r.RoomType;
                    dr[3] = r.RoomPrice;
                    dr[4] = r.Are;
                    dr[5] = r.Address;
                    //if (r.RoomState == 0)
                    //    dr[6] = "开放";
                    //else
                    //    dr[6] = "关闭";

                    dt.Rows.Add(dr);
                }
                return dt;
            }
            catch (Exception ex)
            {
                throw ex;
            }
        }
        public void databind(GridView gdv)
        {
            QPS.NEW.BLL.Enterprise user = new QPS.NEW.BLL.Enterprise();
            QPS.NEW.Model.Room Mroom = new QPS.NEW.Model.Room();
            QPS.NEW.BLL.Room Broom = new QPS.NEW.BLL.Room();
            QPS.NEW.BLL.Orderform Border = new QPS.NEW.BLL.Orderform();
            List<QPS.NEW.Model.Room> roomList = new List<QPS.NEW.Model.Room>();
            if (Session["username"] != null)
            {
                string uname = Session["username"].ToString();
                DataSet dsUser = user.GetList("Username='" + uname + "'");
                int uid = Convert.ToInt32(dsUser.Tables[0].Rows[0]["Id"]);
                roomList = Broom.GetModelList("OwnerID='" + uid + "'");
            }
            gdv.DataSource = Gettable(roomList);
            gdv.DataBind();
        }
        protected void Page_Load(object sender, EventArgs e)
        {
            if (!IsPostBack)
            {
                databind(this.gdvRoom);
            }
        }

        protected void gdvPersonnalOrder_RowDeleting(object sender, GridViewDeleteEventArgs e)
        {
            //得到单位编号
            string rowToDelete = this.gdvRoom.DataKeys[e.RowIndex].Values[0].ToString();
            //转换为整数
            int ID = Convert.ToInt32(rowToDelete);
            QPS.NEW.BLL.Orderform Border = new QPS.NEW.BLL.Orderform();
            QPS.NEW.BLL.Room Broom = new QPS.NEW.BLL.Room();
            if (Broom.GetModel(ID).RoomState == 1)//说明此房间被预定需要从订单中删除
            {
                DataSet dsOrder = Border.GetList("Roomid='" + ID + "'");
                int Oid = Convert.ToInt32(dsOrder.Tables[0].Rows[0]["Id"]);
                Border.Delete(Oid);
            }
            Broom.Delete(ID);
            databind(gdvRoom);
        }

        protected void lbtCreateRoom_Click(object sender, EventArgs e)
        {
            Response.Redirect("Room.aspx");
        }

        protected void gdvRoom_RowUpdating(object sender, GridViewUpdateEventArgs e)
        {
            string roomid = this.gdvRoom.DataKeys[e.RowIndex].Values[0].ToString();
            int ID = Convert.ToInt32(roomid);
            Response.Write("<script>window.open('RoomMod.aspx?roomid="+ID+"', 'newwindow', 'height=600, width=850, toolbar=no, menubar=no, scrollbars=no, resizable=no, location=no, status=no')</script>");
        }
    }
}
