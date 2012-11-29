using System;
using System.Collections.Generic;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;
using System.Data;
using Bzw.Data;
using Utility;
using BCST.Common;

namespace Bzw.Web.Admin.SConfig
{
	public partial class GMAwardTypeSet :AdminBasePage
	{
		public int line=1;
		protected string _id = CommonManager.Web.Request( "id", "" );
		protected string result = string.Empty;
		protected string id
		{
			get
			{
				return _id;
			}
		}
		protected void Page_Load( object sender, EventArgs e )
		{
			string type = CommonManager.Web.Request( "type", "" );
			if( !IsPostBack )
			{
				BindData();
			}
			if( type == "delete" )
			{
				DeleteData();
			}
		}
		//绑定数据
		protected void BindData()
		{
			string sql = "select * from TGM＿AwardType";
			DataTable dt=DbSession.Default.FromSql(sql).ToDataTable();
			rptMain.DataSource = dt;
			rptMain.DataBind();
		}
		//获取道具名
		protected string GetPropName(string propId)
		{
			string sql = "select PropName from TPropDefine where PropID=@propId";
			return DbSession.Default.FromSql( sql )
				.AddInputParameter( "@propId", DbType.String, propId )
				.ToScalar().ToString();
		}
		//删除数据
		protected void DeleteData()
		{
			string sql = "delete TGM＿AwardType where SeriNo=@Id";
			result = DbSession.Default.FromSql( sql )
				.AddInputParameter( "@Id", DbType.String, id )
				.Execute().ToString();
			if( result == "1" )
			{
				CommonManager.Web.RegJs( this, "alert('恭喜您！删除成功')", false );
				BindData();
			}
		}
	}
}
