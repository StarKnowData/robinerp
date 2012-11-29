using System;
using System.Data;
using System.Configuration;
using System.Collections;
using System.Web;
using System.Web.Security;
using System.Web.UI;
using System.Web.UI.WebControls;
using System.Web.UI.WebControls.WebParts;
using System.Web.UI.HtmlControls;
using Utility;
using BCST.Common;
using Bzw.Data;

public partial class Admin_Prizes_PrizesHDel : AdminBasePage
{
    string Logids;
    protected void Page_Load(object sender, EventArgs e)
    {
        AdminPopedom.IsHoldModel("11");

		string tmp = CommonManager.Web.Request( "id", "" );
		if( string.IsNullOrEmpty( tmp ) || !CommonManager.String.IsInteger( tmp ) )
		{
			Alert( "请勿非法操作！", null );
			return;
		}
		else
			Logids = tmp; //Limit.editCharacter(Limit.getFormValue("id"));

      

        string sql = "delete from Web_AwardLog where log_id=" + Logids + "";
        //sqlconn.sqlReader(sql);
		DbSession.Default.FromSql( sql ).Execute();

		string adminName = AdminInfo["UserName"].ToString();
        string descript = "删除兑奖记录资料！" ;
        string system = Common.GetOS;
        new BLL.Member().InsertAdminModifyLog(adminName, Common.RequestIP, system, descript, 1);

		Response.Write( "<script>alert('温馨提示：\\n\\n删除操作成功！');location.href='PrizesH.aspx';</script>" );
    }
}
