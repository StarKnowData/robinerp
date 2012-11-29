using System;
using System.Collections.Generic;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;
using BCST.Common;
using System.Data;
using Bzw.Data;
using Utility;
 
    public partial class Admin_Users_UnLockUser :AdminBasePage
    {
        int userlistid;
        protected void Page_Load(object sender, EventArgs e)
        {
            AdminPopedom.IsHoldModel("04");

        
            string uid = CommonManager.Web.Request("id", "");
            if (string.IsNullOrEmpty(uid) || !CommonManager.String.IsInteger(uid))
            {
                CommonManager.Web.RegJs(this, "alert('参数错误！');", false);
                return;
            }
            userlistid = int.Parse(uid);


            DbSession.Default.FromSql(" update [TUserInfo] set MathineCode='',LockMathine=0 Where UserID=@UserID").AddInputParameter("@UserID", DbType.Int32, uid).Execute();

            string descript = "解锁游戏用户ID为" + uid ;
            string system = Common.GetOS;

            new BLL.Member().InsertAdminModifyLog(AdminInfo["UserName"].ToString(),Common.RequestIP, system, descript, 1);
      
            Response.Write("<script>alert('温馨提示：\\n\\n解锁操作成功！');location.href='User_List.aspx';</script>");
        }
    }
 
