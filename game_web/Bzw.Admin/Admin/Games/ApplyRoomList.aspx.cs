using System;
using System.Collections.Generic;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;
using System.Text;
using BCST.Common;
using System.Data;
using Bzw.Data;

 
    public partial class Admin_Games_ApplyRoomList : AdminBasePage
    {
        protected void Page_Load(object sender, EventArgs e)
        {
            AdminPopedom.IsHoldModel("06");
            StringBuilder where = new StringBuilder(); //查询条件构造函数
            #region 设置搜索条件
            string key = CommonManager.Web.RequestUrlDecode("key", "");  //获取从URL中传过来的值
            string sta = CommonManager.Web.RequestUrlDecode("status", "3");
            if (key != "")
            {
                where.AppendFormat(" and UserName='{0}'", key); 
            }
            if (!string.IsNullOrEmpty(sta) && sta != "3")
            {
                where.AppendFormat(" and AuditStatus={0}", sta);
            }
            #endregion
            DataSet ds = DbSession.Default.FromProc("Web_pGetDataPager")    //执行分页的存储过程
             .AddInputParameter("@PageSize", DbType.Int32, anpPageIndex.PageSize)  //当前页码显示的数据
             .AddInputParameter("@CurrentPage", DbType.Int32, PageIndex)  //页码的索引
             .AddInputParameter("@Columns", DbType.String, "*")          //需要获取哪些列
             .AddInputParameter("@TableName", DbType.String, "Web_VApplyVipRoom")  //表或视图的名称
             .AddInputParameter("@Wheres", DbType.String, where.ToString())  //查询条件
             .AddInputParameter("@KeyName", DbType.String, "AddDate")     //设置主键的名称
             .AddInputParameter("@OrderBy", DbType.String, "AddDate desc")  //设置排序的字段
             .ToDataSet();                                        //执行数据查询语句

            if (ds.Tables.Count > 0)
            {

                anpPageIndex.RecordCount = (int)ds.Tables[0].Rows[0][0]; //获取总的记录条数
                anpPageIndex.CurrentPageIndex = PageIndex;   //  获取页码的索引
                if (ds.Tables[1].Rows.Count > 0)
                {
                    rptRoomList.DataSource = ds.Tables[1];  //获取数据表中的数据
                    rptRoomList.DataBind();       //将数据绑定到分页空间上
                    rptRoomList.Visible = true;  //设置分页控件可不可用
                    ltNonData.Visible = false;  //设置要不要显示 “无记录语句”
                }
                else
                {
                    rptRoomList.Visible = false;
                    ltNonData.Visible = true;
                }
            }

        }
        
    }
 
