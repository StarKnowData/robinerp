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


namespace Bzw.Inhersits
{
	public partial class Bulletin : UiCommon.AppBasePage
	{
		/// <summary>
		/// form1 控件。
		/// </summary>
		/// <remarks>
		/// 自动生成的字段。
		/// 要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
		/// </remarks>
		protected global::System.Web.UI.HtmlControls.HtmlForm form1;

		public string Content = "暂无公告";

		protected void Page_Load( object sender, EventArgs e )
		{
			if( !IsPostBack )
			{
				string sql = "select content from Web_NewsType,Web_NewsData where Web_NewsType.typeid=Web_NewsData.News_Type and typesort=100 and istop=1";
				object obj = Utility.SqlHelper.ExecuteScalar( CommandType.Text, sql, null );
				if( obj != null )
				{
					Content = obj.ToString();
				}

			}
		}
	}
}
