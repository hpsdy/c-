// Copyright 2013 Baidu.com  All Rights Reserved.
// Author: wangguangyuan@baidu.com (Guangyuan Wang)
#ifndef  INDEX_DIMENSION_DOC_MANAGER_H
#define  INDEX_DIMENSION_DOC_MANAGER_H

#include <map>
#include <set>
#include <string>
#include <ext/hash_map>
#include "bsl/containers/hash/bsl_phashmap.h"
#include "Configure.h"
#include "unise/annotation_schema.pb.h"
#include "unise/base.h"
#include "unise/dimension_doc.h"
#include "unise/fact_doc.h"
#include "unise/doc_factory.h"
#include "unise/boost_wrap.h"
#include "unise/skiplist.h"

namespace unise {
class BaseBuilder;

struct filter_relation_ship_t {
    uint32_t foreign_key;  ///< fact_doc的annotation id，其annotation的取值是dimension docid
    uint32_t level_id;     ///< dimension doc的level id
    uint32_t relation_key; ///< dimension doc的annotation id
    std::set<uint64_t> filted_values;   ///< dimension doc的被过滤掉的值
};

class DimensionDocManager
{
public:
    typedef __gnu_cxx::hash_map<DocId, SkipList<DocId> * > d2f_map_t;
    typedef bsl::phashmap<DocId, DimensionDoc*> DimensionDocMap;
    // note: the family map has a few elements, map is better than hash map
    typedef std::map<std::string, size_t> DimensionDocFamilyMap;
    struct dimension_t {
        dimension_t(): id(-1), doc_map(NULL), factory(NULL) {
        }
        ~dimension_t() {
            if (NULL != factory) {
                for (DimensionDocMap::iterator doc_it = doc_map->begin();
                     doc_it != doc_map->end();
                     ++doc_it) {
                    factory->destroy(doc_it->second);
                }
                delete factory;
                factory = NULL;
                delete doc_map;
                doc_map = NULL;
            }
        }
        int id;
        std::string name;
        DimensionDocMap *doc_map;
        DocFactory * factory;
    };

    DimensionDocManager();
    ~DimensionDocManager();

    /**
     * @brief 初始化函数
     *
     * @param [in] : 一个[@DimensionDoc]的配置数组
     * @param [out] : none
     * @return  bool
     * @retval true,配置初始化成功；否则初始化失败
     * @see
     * @note
    **/
    bool init(const comcfg::ConfigUnit& conf);

    /**
     * @brief 根据DimensionDoc的level_id和字符串，构造一个DimensionDoc对象
     *
     * @param [in] : level_id为DimensionDoc的层级id，与配置中的Id对应
     * @param [in] : str为字符串格式标识的一个doc
     * @param [in] : record为增量数据信息
     * @param [out] : none
     * @return DimensionDoc*
     * @retval 非NULL，构造成功；NULL，构造失败
     * @see
     * @note 返回的指针，外部不能够delete
     *       单个写线程调用，不可多线程调用
    **/
    DimensionDoc * add_dimension_doc(size_t level_id,
            const std::string& str,
            const das_inc_record_t& record);

    /**
     * @brief 根据DimensionDoc的level_id和docid，获取DimensionDoc指针
     *
     * @param [in] : level_id为DimensionDoc的层级id，与配置中的Id对应
     * @param [in] : docid为DimensionDoc的docid
     * @param [out] : none
     * @return const DimensionDoc*
     * @retval 非NULL，获取成功
     * @see
     * @note 返回的指针，外部不能够delete，且只能调用const方法
     *       多线程安全，但是获取的指针在一定时间后会失效
    **/
    inline const DimensionDoc * get_dimension_doc(size_t level_id, DocId docid) const
    {
        DimensionDoc *ret = NULL;
        if (level_id < _dimensions.size() && _dimensions[level_id].doc_map != NULL) {
            _dimensions[level_id].doc_map->get(docid, &ret);
        }
        return ret;
    }

    /**
     * @brief 根据DimensionDoc的dimension_name和docid，获取DimensionDoc指针
     *
     * @param [in] : dimension_name为DimensionDoc的族类名
     * @param [in] : docid为DimensionDoc的docid
     * @param [out] : none
     * @return const DimensionDoc*
     * @retval 非NULL，获取成功
     * @see
     * @note 返回的指针，外部不能够delete，且只能调用const方法
     *       多线程安全，但是获取的指针在一定时间后会失效
    **/
    inline const DimensionDoc * get_dimension_doc(
                const std::string & dimension_name, DocId docid) const
    {
        DimensionDocFamilyMap::const_iterator family_it = _family_map.find(dimension_name);
        if (family_it == _family_map.end()) {
            return NULL;
        }
        return get_dimension_doc(family_it->second, docid);
    }

    /**
     * @brief 根据FactDoc的docid，获取常指针
     *
     * @param [in] : docid为FactDoc的docid
     * @param [out] : none
     * @return const FactDoc*
     * @retval 非NULL，获取成功
     * @see
     * @note 返回的指针，外部不能够delete，且只能调用const方法
     *       多线程安全，但是获取的指针在一定时间后会失效
    **/
    inline const FactDoc * get_fact_doc(DocId docid) const
    {
        DimensionDoc *ret = NULL;
        GOOGLE_DCHECK(_fact_doc_id < _dimensions.size());
        GOOGLE_DCHECK(_dimensions[_fact_doc_id].doc_map != NULL);
        _dimensions[_fact_doc_id].doc_map->get(docid, &ret);
        return dynamic_cast<const FactDoc*>(ret);
    }

    /**
     * @brief 根据DimensionDoc的level_id和docid，删除DimensionDoc在索引中的存在
     *
     * @param [in] : level_id为DimensionDoc的层级id
     * @param [in] : docid为DimensionDoc的docid
     * @param [in] : record为增量数据信息
     * @param [out] : none
     * @return none
     * @retval none
     * @see
     * @note 找不到level_id，找不对应的docid，不执行删除操作，会打印WARNING LOG
    **/
    void delete_dimension_doc(size_t level_id, 
            DocId docid, 
            const das_inc_record_t& record);

    /**
     * @brief 获取FactDoc的名字，配置中，有且仅有一种DimensionDoc是一种FactDoc
     *
     * @param [in] : none
     * @param [out] : none
     * @return const std::string&
     * @retval FactDoc名字的引用
     * @see
     * @note
    **/
    const std::string & get_fact_doc_dimension_name() const { return _fact_doc_name; }

    /**
     * @brief 获取FactDoc的level_id
     *
     * @param [in] : none
     * @param [out] : none
     * @return size_t
     * @retval FactDoc的层级id
     * @see
     * @note
    **/
    inline size_t get_fact_doc_level_id() const { return _fact_doc_id; }

    /**
     * @brief 获取_d2f_maps
     *
     * @param [in] : none
     * @param [out] : none
     * @return std::vector<d2f_map_t *>
     * @retval 
     * @see
     * @note
    **/
    std::vector<d2f_map_t *> get_d2f_maps() const { return _d2f_maps; }

    /**
     * @brief 设置_d2f_maps
     *
     * @param [in] : std::vector<d2f_map_t *>
     * @param [out] : none
     * @return 
     * @retval 
     * @see
     * @note
    **/
    void set_d2f_maps(std::vector<d2f_map_t *> d2f_maps) { _d2f_maps = d2f_maps; }

    /**
     * @breaf 判断level id标明的DimensionDoc是否存在
     *
     * @param [in] : none
     * @param [out] : none
     * @return bool
     * @retval true则存在
     * @see
     * @note
    **/
    bool dimension_doc_exist(size_t level_id) const;

    /**
     * @brief 根据级联配置，以及当前所有相关dimension doc的状态
     *        返回fact doc对应的flag位
     *        并构造内部的反查hashmap
     * @note 在doc_builder和fact_doc_base_builder中调用
     */
    uint8_t add_fact_doc_filter_relation(const FactDoc& doc);

    void remove_fact_doc_filter_relation(const FactDoc& doc);

    /**
     * @brief 每当add_dimension_doc和delete_dimension_doc之后
     *        通过该函数获取受级联影响的fact_doc的docid
     * @note 只考虑非fact_doc的add和delete
     * @warning 这个函数只在das_inc_builder中调用
     */
    const SkipList<DocId> * get_filt_relation_docids(uint8_t * flag, uint8_t * mask) const;

private:
    bool init_filter_relation_ship(const std::string& path);
    void add_relation_ship(uint32_t dim_level_id, DocId dim_id, DocId fact_id);
    void remove_relation_ship(uint32_t dim_level_id, DocId dim_id, DocId fact_id);
    void relation_ship_filt(uint32_t level_id, const DimensionDoc& doc, bool is_delete);
    /**
     * @brief 在add和delete的时候首先调用
     *        保证add和delete之后，操纵级联过滤时，
     *        取到的是合法的值
     */
    void reset_cascade_status() {
        // 首先清空需要级联过滤的fact doc的id
        _relation_docids = NULL;
        // 代表某个二进制位是过滤位，是否过滤见relation_flag
        _relation_mask = 0;
        // 代表是否被过滤
        _relation_flag = 0;
    }

private:
    // from name to id
    DimensionDocFamilyMap _family_map;
    // from id to dimension_t
    std::vector<dimension_t>    _dimensions;    ///< 所有的维度表
    // the fact doc name
    std::string _fact_doc_name;
    // the fact doc level id
    size_t _fact_doc_id;
    std::vector<filter_relation_ship_t> _filters;
    bool _need_filter;

    std::vector<d2f_map_t *> _d2f_maps; ///< 存储不同level的dimension_to_factdocs

    const SkipList<DocId> * _relation_docids;
    uint8_t _relation_flag;
    uint8_t _relation_mask;

    friend class BaseBuilder;
    friend class DimensionDocBaseBuilder;
    friend class FactDocBaseBuilder;

private:
    GOOGLE_DISALLOW_EVIL_CONSTRUCTORS(DimensionDocManager);
};
}

#endif  // INDEX_DIMENSION_DOC_MANAGER_H

/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
