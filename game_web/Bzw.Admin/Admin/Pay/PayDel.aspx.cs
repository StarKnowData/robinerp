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

public partial class Admin_Pay_PayDel : AdminBasePage
{
    string payid, typepayid;
    protected void Page_Load(object sender, EventArgs e)
    {
        AdminPopedom.IsHoldModel("05");

		string tmp = CommonManager.Web.Request( "id", "" );
		if( string.IsNullOrEmpty( tmp ) || !CommonManager.String.IsInteger( tmp ) )
		{
			Alert( "请勿非法操作！", null );
			return;
		}
		else
			payid = tmp; //Limit.editCharacter(Limit.getFormValue("id"));

		typepayid = CommonManager.Web.Request( "pay", "" );//Limit.editCharacter(Limit.getFormValue("pay"));
        string sql = "delete  from web_card where id=" + payid + "";
		//sqlconn.sqlReader(sql);
		//Limit.outMsgBox("温馨提示：\\n\\n删除操作成功！", "Pay.aspx?pay=" + typepayid + "", true);
		DbSession.Default.FromSql( sql ).Execute();
        Response.Write("<script>alert('删除操作成功！');location.href='" + Server.UrlDecode(Utility.Common.GetStringOfUrl("url")) + "';</script>");
    }
}
