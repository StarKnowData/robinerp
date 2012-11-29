using System;
using System.Collections.Generic;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;
using System.Data;
using Bzw.Data;
using BCST.Common;
using Utility;

  public partial class Admin_Users_EditUserPoint : AdminBasePage
    {
   
        protected void Page_Load(object sender, EventArgs e)
        {
            if (!IsPostBack)
            {
                string userid = Utility.Common.GetStringOfUrl("uid");
                string nameid = Utility.Common.GetStringOfUrl("nameid");
                if (string.IsNullOrEmpty(userid) || !Utility.Common.IsNumber(userid) || string.IsNullOrEmpty(nameid) || !Utility.Common.IsNumber(nameid))
                {
                    CommonManager.Web.RegJs(this, "alert('参数错误。');", false);
                    return;
                }
                DataTable dt = DbSession.Default.FromSql("select * from Web_vUserPoint where userid="+userid+" and nameid="+nameid).ToDataTable();
                if (dt.Rows.Count > 0)
                {
                    lblComName.Text = dt.Rows[0]["ComName"].ToString();
                    lblUserID.Text = dt.Rows[0]["UserID"].ToString();
                    lblUserName.Text = dt.Rows[0]["UserName"].ToString();
                    txtNewPoint.Text = dt.Rows[0]["Point"].ToString();
                    hidNameID.Value = dt.Rows[0]["NameID"].ToString();
                   lblPoint.Text = dt.Rows[0]["Point"].ToString();
                }
            }
        }

        protected void Button1_Click(object sender, EventArgs e)
        {
            string newPoint = txtNewPoint.Text.Trim();
            if (!Utility.Common.IsNumber(newPoint))
            {
                CommonManager.Web.RegJs(this, "alert('积分必须为整数。');", false);
                return;
            }
            
                Int64 point2 = Convert.ToInt64(lblPoint.Text.Trim());
                string userid = lblUserID.Text.Trim();
                string nameid = hidNameID.Value;
            if(point2!=Convert.ToInt64(newPoint))
            {
                int i = DbSession.Default.FromSql("Update TmatchTable set Point=@Point where UserID=@UserID and NameID=@NameID").AddInputParameter("@Point", DbType.Int64,newPoint)
                                            .AddInputParameter("@UserID", DbType.Int32, userid)
                                            .AddInputParameter("@NameID", DbType.Int32, nameid)
                                            .Execute();
                if (i > 0)
                {
                    //管理员操作日志
                    string descript = "修改用户的积分，用户ID为" + userid + "，将积分从" + point2 + "改为" + newPoint;
                    string system = Common.GetOS;
                    new BLL.Member().InsertAdminModifyLog(AdminInfo["UserName"].ToString(), Common.RequestIP, system, descript, 1);
                    Response.Write("<script>alert('温馨提示：\\n\\n修改成功！');location.href=location.href; </script>");
                }
            }
        }
        
    }
 
