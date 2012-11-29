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
	public partial class ShowGameHtml : UiCommon.AppBasePage
	{
		/// <summary>
		/// Head1 控件。
		/// </summary>
		/// <remarks>
		/// 自动生成的字段。
		/// 要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
		/// </remarks>
		protected global::System.Web.UI.HtmlControls.HtmlHead Head1;

		/// <summary>
		/// form1 控件。
		/// </summary>
		/// <remarks>
		/// 自动生成的字段。
		/// 要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
		/// </remarks>
		protected global::System.Web.UI.HtmlControls.HtmlForm form1;
		public string GameName = string.Empty;
		public string GameInfo = "非常抱歉,尚未添加该游戏的规则内容,我们会尽快完善!";

		protected void Page_Load( object sender, EventArgs e )
		{
			if( !IsPostBack )
			{
				string id = Utility.Common.SqlEncode( Utility.Common.GetStringOfUrl( "id" ) );
				if( string.IsNullOrEmpty( id ) || !BCST.Common.CommonManager.String.IsInteger( id ) )
				{
					Response.Write( "参数调用出错!" );
					Response.End();
					return;
				}

				string sql = "select top 1 Game_Rule,Game_Name from Web_GameInfo  where game_id=" + id;
				IDataReader dr = Utility.SqlHelper.ExecuteReader( CommandType.Text, sql, null );
				if( dr.Read() )
				{

					GameInfo = dr.GetString( 0 ).ToString();//游戏的规则内容
					GameName = dr.GetString( 1 ).ToString();
				}
				else
				{
					Response.Write( "非常抱歉,尚未添加该游戏的规则内容,我们会尽快完善!" );
					Response.End();

				}
				dr.Close();
				dr.Dispose();


			}
		}
	}
}
