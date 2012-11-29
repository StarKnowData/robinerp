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
using BCST.Common;
using Bzw.Data;

public partial class Admin_Promotion_PrDel : AdminBasePage
{
    string PrID;
    protected void Page_Load(object sender, EventArgs e)
    {
        AdminPopedom.IsHoldModel("13");

		string tmp = CommonManager.Web.Request( "id", "" );
		if( string.IsNullOrEmpty( tmp ) || !CommonManager.String.IsInteger( tmp ) )
		{
			Alert( "请勿非法操作！", null );
			return;
		}
		else
			PrID = tmp;//Limit.editCharacter(Limit.getFormValue("id"));
        string sql = "delete from Web_Tuiguang where id=" + PrID + "";
		//sqlconn.sqlReader(sql);
		DbSession.Default.FromSql( sql ).Execute();
		//Limit.outMsgBox("温馨提示：\\n\\n删除操作执行成功！", "PrList.aspx", true);
		Response.Write( "<script>alert('温馨提示：\\n\\n删除操作成功！');location.href='PrList.aspx';</script>" );
    }
}
