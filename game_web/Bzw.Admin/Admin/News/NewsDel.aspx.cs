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

public partial class Admin_News_NewsDel : AdminBasePage
{
    string DelId;
    protected void Page_Load(object sender, EventArgs e)
    {
        AdminPopedom.IsHoldModel("10");

		string tmp = CommonManager.Web.Request( "id", "" );
		if( string.IsNullOrEmpty( tmp ) || !CommonManager.String.IsInteger( tmp ) )
		{
			Alert( "请勿非法操作！", null );
			return;
		}
		else
			DelId = tmp;
		//Limit.editCharacter( Limit.getFormValue( "id" ) );
        string title = string.Empty;
        string sql1 = "select * from Web_NewsData where News_id=" + DelId + "";
		DataTable dt = DbSession.Default.FromSql( sql1 ).ToDataTable(); //sqlconn.sqlReader(sql1);
         if (dt.Rows.Count > 0)
         {
             title = dt.Rows[0]["Title"].ToString(); 
         }
         dt.Clear();

        string sql = "delete from Web_NewsData where News_id=" + DelId + "";
        //sqlconn.sqlReader(sql);
		DbSession.Default.FromSql( sql ).Execute();
		string adminName = AdminInfo["UserName"].ToString();
        string descript = "删除新闻内容！标题：" + title ;
        string system = Common.GetOS;
		new BLL.Member().InsertAdminModifyLog( adminName, Common.RequestIP, system, descript, 1 );
		Response.Write( "<script>alert('删除操作执行成功！');location.href='News.aspx';</script>" );
    }
}
