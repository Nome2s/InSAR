#pragma once
#ifndef __FORMATCONVERSION__H__
#define __FORMATCONVERSION__H__
#include<string>
#include"..\include\Package.h"
#include"..\include\ComplexMat.h"
#include"Utils.h"
#include"hdf5.h"
#include"..\include\tinyxml.h"
#define Big2Little64(A) ((uint64_t)(A&0xff00000000000000)>>56|(A&0x00ff000000000000)>>40|(A&0x0000ff0000000000)>>24|(A&0x000000ff00000000)>>8|(A&0x00000000ff000000)<<8|(A&0x0000000000ff0000)<<24|(A&0x000000000000ff00)<<40|(A&0x00000000000000ff)<<56)
#define Big2Little32(A) ((uint32_t)(A&0xff000000)>>24|(uint32_t)(A&0x00ff0000)>>8 | (uint32_t)(A&0x0000ff00)<<8|(uint32_t)(A&0x000000ff)<<24)
#define Big2Little16(A) ((uint16_t)(A&0xff00)>>8 | (uint16_t)(A&0x00ff)<<8)
/*********************************************************/
/***************   XML�ļ�������д���    ****************/
/*********************************************************/

class InSAR_API XMLFile
{
public:
	XMLFile();
	~XMLFile();

	/** @brief �����µĹ����ļ�
	
	@param project_path       ����·��
	@param project_name       ������
	@param project_version    �����ļ��汾
	*/
	int XMLFile_creat_new_project(
		const char* project_path,
		const char* project_name,
		const char* project_version
	);
	/** @brief ��ӵ���ԭʼ���ݽڵ�

	@param datanode_node  �ڵ���
	@param node_name      ͼ����
	@param node_path      ͼ��·��
	@param sensor         ����
	*/
	int XMLFile_add_origin(
		const char* datanode_node,
		const char* node_name,
		const char* node_path,
		const char* sensor = "unknown"
	);
	/*@brief ��ӵ���ԭʼ���ݽڵ�(14_project)
	* @param datanode_node  �ڵ���
	* @param node_name      ͼ����
	* @param node_path      ͼ��·��
	* @param mode           �շ�ģʽ��1���������գ�2������˫�գ�3��ƹ�ң�4��˫Ƶƹ�ң�
	* @param sensor         ����
	*/
	int XMLFile_add_origin_14(
		const char* datanode_node,
		const char* node_name,
		const char* node_path,
		int mode = 1,
		const char* sensor = "unknown"
	);
	/** @brief ��Ӳü�ͼ��ڵ�

	@param datanode_node  �ü�ͼ��ڵ���
	@param master_index   �ü��ڵ���ͼ��ţ�1-based��
	@param node_name      �ü�ͼ����
	@param node_path      �ü�ͼ��·��
	@param Row_offset     ��ƫ����
	@param Col_offset     ��ƫ����
	@param lon            ���ľ���
	@param lat            ����γ��
	@param width          �ü����
	@param height         �ü��߶�
	@param data_rank      ���ݵȼ�
	*/
	int XMLFile_add_cut(
		const char* datenode_name,
		int master_index,
		const char* node_name,
		const char* node_path,
		int Row_offset,
		int Col_offset,
		double lon, double lat,
		double width, double height,
		const char* data_rank
	);

	/** @brief ��Ӳü�ͼ��ڵ�
	@param datanode_node  �ü�ͼ��ڵ���
	@param master_index   �ü��ڵ���ͼ��ţ�1-based��
	@param node_name      �ü�ͼ����
	@param node_path      �ü�ͼ��·��
	@param Row_offset     ��ƫ����
	@param Col_offset     ��ƫ����
	@param lon            ���ľ���
	@param lat            ����γ��
	@param width          �ü����
	@param height         �ü��߶�
	@param data_rank      ���ݵȼ�
	*/
	int XMLFile_add_cut_14(
		const char* datanode_name,
		int master_index,
		const char* node_name,
		const char* node_path,
		int Row_offset,
		int Col_offset,
		double lon, double lat,
		double width, double height,
		const char* data_rank
	);

	/** @brief �����׼ͼ��ڵ�

	@param datanode_node  ��׼ͼ��ڵ���
	@param node_name      ��׼ͼ����
	@param node_path      ��׼ͼ��·��
	@param Row_offset     ��ƫ����
	@param Col_offset     ��ƫ����
	@param master_index   ��ͼ�����
	@param interp_times   ��ֵ������2��n���ݣ�
	@param block_size     �ӿ�ߴ磨2��n���ݣ�
	@param temporal_baseline ʱ����߹���
	@param B_effect       ��ֱ���߹���
	@param B_parallel     ˮƽ���߹���
	*/
	int XMLFile_add_regis(
		const char* datanode_name,
		const char* node_name,
		const char* node_path,
		int Row_offset,
		int Col_offset,
		int master_index, int interp_times, int block_size,
		const char* temporal_baseline, const char* B_effect, const char* B_parallel
	);

	/** @brief �����׼ͼ��ڵ�
	@param mode           �շ�ģʽ��1���������գ�2������˫�գ�3��ƹ�ң�4��˫Ƶƹ�ң�
	@param datanode_node  ��׼ͼ��ڵ���
	@param node_name      ��׼ͼ����
	@param node_path      ��׼ͼ��·��
	@param Row_offset     ��ƫ����
	@param Col_offset     ��ƫ����
	@param master_index   ��ͼ�����
	@param interp_times   ��ֵ������2��n���ݣ�
	@param block_size     �ӿ�ߴ磨2��n���ݣ�
	@param temporal_baseline ʱ����߹���
	@param B_effect       ��ֱ���߹���
	@param B_parallel     ˮƽ���߹���
	*/
	int XMLFile_add_regis14(
		int mode,
		const char* datanode_name,
		const char* node_name,
		const char* node_path,
		int Row_offset,
		int Col_offset,
		int master_index, int interp_times, int block_size,
		const char* temporal_baseline, const char* B_effect, const char* B_parallel
	);

	/*@brief ��Ӻ�����������׼�ڵ�
	* @param dataNode            ��׼ͼ�����ݽڵ���
	* @param dataName            ��׼ͼ��������
	* @param dataPath            ��׼ͼ�����ݴ���·�������·����
	* @param masterIndex         ��ͼ�����
	* @return �ɹ�����0�����򷵻�-1
	*/
	int XMLFile_add_backgeocoding(
		const char* dataNode,
		const char* dataName,
		const char* dataPath,
		int masterIndex
	);
	/*@brief ��ӵ��Ӹ�ͼ��ȥ�ο���λ�ڵ�
	* @param dataNode            ��׼ͼ�����ݽڵ���
	* @param dataName            ��׼ͼ��������
	* @param dataPath            ��׼ͼ�����ݴ���·�������·����
	* @param masterIndex         ��ͼ�����
	* @return �ɹ�����0�����򷵻�-1
	*/
	int XMLFile_add_SLC_deramp(
		const char* dataNode,
		const char* dataName,
		const char* dataPath,
		int masterIndex
	);

	/*@brief ��ӵ��Ӹ�ͼ��ȥ�ο���λ�ڵ�
	* @param mode                �շ�ģʽ��1���������գ�2������˫�գ�3��ƹ��ģʽ��4��˫Ƶƹ��ģʽ��
	* @param dataNode            ��׼ͼ�����ݽڵ���
	* @param dataName            ��׼ͼ��������
	* @param dataPath            ��׼ͼ�����ݴ���·�������·����
	* @param masterIndex         ��ͼ�����
	* @return �ɹ�����0�����򷵻�-1
	*/
	int XMLFile_add_SLC_deramp_14(
		int mode,
		const char* dataNode,
		const char* dataName,
		const char* dataPath,
		int masterIndex
	);

	/*@brief ���С���߼�ʱ�����з����ڵ�
	* @param dataNode            SBASʱ�����з������ݽڵ���
	* @param dataName            SBASʱ�����з���������
	* @param dataPath            SBASʱ�����з���ͼ�����ݴ���·�������·����
	* @return �ɹ�����0�����򷵻�-1
	*/
	int XMLFile_add_SBAS(
		const char* dataNode,
		const char* dataName,
		const char* dataPath
	);
	/*@brief ����ڱ�һ��burstƴ�ӽڵ�
	* @param dataNode            deburstͼ�����ݽڵ���
	* @param dataName            deburstͼ��������
	* @param dataPath            deburstͼ�����ݴ���·�������·����
	* @return �ɹ�����0�����򷵻�-1
	*/
	int XMLFile_add_S1_Deburst(
		const char* dataNode,
		const char* dataName,
		const char* dataPath
	);
	/*@brief ��ӵ������ڵ�
	* @param dataNode            �������ͼ�����ݽڵ���
	* @param dataName            �������ͼ��������
	* @param dataPath            �������ͼ�����ݴ���·�������·����
	* @param level               ���ݵȼ�
	* @return �ɹ�����0�����򷵻�-1
	*/
	int XMLFile_add_geocoding(
		const char* dataNode,
		const char* dataName,
		const char* dataPath,
		const char* level
	);

	/*@brief ��Ӹ�����λ���ɽڵ�
	* @param datanode_node                 ������λͼ��ڵ���
	* @param node_name                     ������λͼ����
	* @param node_path                     ������λͼ��·��
	* @param master_name                   ������λ��ͼ��
	* @param rank                          �ڵ�ȼ�
	* @param offset_row                    ��ͼ����ƫ����
	* @param offset_col                    ��ͼ����ƫ����
	* @param multilook_rg                  ���ӱ�����������
	* @param multilook_az                  ���ӱ�������λ��
	* @return �ɹ�����0�����򷵻�-1
	*/
	int XMLFile_add_interferometric_phase_14(
		const char* datanode_name,
		const char* node_name,
		const char* node_path,
		const char* master_name,
		const char* rank,
		int offset_row,
		int offset_col,
		int multilook_rg,
		int multilook_az
	);

	/** @brief ��Ӹ�����λ���ɽڵ�

	@param datanode_node  ������λͼ��ڵ���
	@param node_name      ������λͼ����
	@param node_path      ������λͼ��·��
	@param master_name    ������λ��ͼ��
	@param rank			  �ڵ�ȼ�
	@param offset_row     ��ͼ����ƫ����
	@param offset_col     ��ͼ����ƫ����
	@param isdeflat       �Ƿ�ȥƽ��
	@param istopo_removal �Ƿ�ȥ����
	@param iscoherence    �Ƿ�������ϵ��
	@param win_w          ���ϵ�����ƴ��ڿ��
	@param win_h          ���ϵ�����ƴ��ڸ߶�
	@param multilook_rg   ���ӱ�����������
	@param multilook_az   ���ӱ�������λ��
	*/
	int XMLFile_add_interferometric_phase(
		const char* datanode_name,
		const char* node_name,
		const char* node_path,
		const char* master_name,
		const char* rank,
		int offset_row, int offset_col,
		int isdeflat, int istopo_removal, int iscoherence,
		int win_w, int win_h, int multilook_rg, int multilook_az
	);

	/** @brief ����˲�ͼ��ڵ�
	@param mode           �շ�ģʽ��1���������գ�2������˫�գ�3��ƹ��ģʽ��4��˫Ƶƹ��ģʽ��
	@param datanode_node  �˲�ͼ��ڵ���
	@param node_name      �˲�ͼ����
	@param node_path      �˲�ͼ��·��
	@param Row_offset     ��ƫ����
	@param Col_offset     ��ƫ����
	@param method		  ��������
	@param Slop_win		  б������Ӧ���ڳߴ�
	@param Pre_win		  Ԥ���ڳߴ�
	@param Goldstein_win  Goldstein�˲�FFT���ڳߴ�
	@param Goldstein_filled_win		Goldstein�˲����㴰�ڳߴ�
	@param alpha		  Goldstein�˲���ֵ
	@param filter_dl_path			���ѧϰ�˲���ִ�г���·��
	@param dl_model_file			���ѧϰ�˲�ģ��·��
	@param tmp_path        ���ѧϰ�˲��м��ļ�·��
	*/
	int XMLFile_add_denoise_14(
		int mode,
		const char* datanode_name,
		const char* node_name,
		const char* node_path,
		int Row_offset,
		int Col_offset,
		const char* method,
		int Slop_win, int Pre_win,
		int Goldstein_win, int Goldstein_filled_win, double alpha,
		const char* filter_dl_path, const char* dl_model_file, const char* tmp_path
	);

	/** @brief ����˲�ͼ��ڵ�

	@param datanode_node  �˲�ͼ��ڵ���
	@param node_name      �˲�ͼ����
	@param node_path      �˲�ͼ��·��
	@param Row_offset     ��ƫ����
	@param Col_offset     ��ƫ����
	@param method		  ��������
	@param Slop_win		  б������Ӧ���ڳߴ�
	@param Pre_win		  Ԥ���ڳߴ�
	@param Goldstein_win  Goldstein�˲�FFT���ڳߴ�
	@param Goldstein_filled_win		Goldstein�˲����㴰�ڳߴ�
	@param alpha		  Goldstein�˲���ֵ
	@param filter_dl_path			���ѧϰ�˲���ִ�г���·��
	@param dl_model_file			���ѧϰ�˲�ģ��·��
	@param tmp_path        ���ѧϰ�˲��м��ļ�·��
	*/
	int XMLFile_add_denoise(
		const char* datanode_name,
		const char* node_name,
		const char* node_path,
		int Row_offset,
		int Col_offset,
		const char* method,
		int Slop_win, int Pre_win,
		int Goldstein_win, int Goldstein_filled_win, double alpha,
		const char* filter_dl_path, const char* dl_model_file, const char* tmp_path
	);
	/** @brief ��ӽ��ͼ��ڵ�

	@param datanode_node  ���ͼ��ڵ���
	@param node_name      ���ͼ����
	@param node_path      ���ͼ��·��
	@param Row_offset     ��ƫ����
	@param Col_offset     ��ƫ����
	@param method		  ��������
	@param threshold	  �ۺϷ���ֵ
	*/
	int XMLFile_add_unwrap(
		const char* datanode_name,
		const char* node_name,
		const char* node_path,
		int Row_offset,
		int Col_offset,
		const char* method,
		double threshold
	);

	/** @brief ��ӽ��ͼ��ڵ�
	@param mode           �շ�ģʽ��1���������գ�2������˫�գ�3��ƹ��ģʽ��4��˫Ƶƹ��ģʽ��
	@param datanode_node  ���ͼ��ڵ���
	@param node_name      ���ͼ����
	@param node_path      ���ͼ��·��
	@param Row_offset     ��ƫ����
	@param Col_offset     ��ƫ����
	@param method		  ��������
	@param threshold	  �ۺϷ���ֵ
	*/
	int XMLFile_add_unwrap_14(
		int mode,
		const char* datanode_name,
		const char* node_name,
		const char* node_path,
		int Row_offset,
		int Col_offset,
		const char* method,
		double threshold
	);

	/** @brief ���Demͼ��ڵ�

	@param datanode_node  Demͼ��ڵ���
	@param node_name      Demͼ����
	@param node_path      Demͼ��·��
	@param Row_offset     ��ƫ����
	@param Col_offset     ��ƫ����
	@param method		  ��������
	@param threshold	  ��������
	*/
	int XMLFile_add_dem(
		const char* datanode_name,
		const char* node_name,
		const char* node_path,
		int Row_offset,
		int Col_offset,
		const char* method,
		int times
	);

	/** @brief ���Demͼ��ڵ�
	@param mode           �շ�ģʽ��1���������գ�2������˫�գ�3��ƹ��ģʽ��4��˫Ƶƹ��ģʽ��
	@param datanode_node  Demͼ��ڵ���
	@param node_name      Demͼ����
	@param node_path      Demͼ��·��
	@param Row_offset     ��ƫ����
	@param Col_offset     ��ƫ����
	@param method		  ��������
	@param threshold	  ��������
	*/
	int XMLFile_add_dem_14(
		int mode,
		const char* datanode_name,
		const char* node_name,
		const char* node_path,
		int Row_offset,
		int Col_offset,
		const char* method,
		int times
	);

	/** @brief ɾ��ͼ��ڵ�
	@param datanode_node  ��ɾ��ͼ��ڵ���
	@param node_name      ��ɾ��ͼ����
	@param node_path      ��ɾ��ͼ��·��
	*/
	int XMLFile_remove_node(
		const char* datanode_name,
		const char* node_name,
		const char* node_path
	);

	/** @brief �����ַ���

	@param n			��������ֵ
	*/
	string int2str(int n);
	/** @brief ��������

	@param s			�����ַ���
	*/
	int str2int(const string& s);
	/** @brief ����XML

	@param save_path    ����·��
	*/
	int XMLFile_save(
		const char* save_path
	);




	/*XML�ļ�����
	* ����1���������ļ���
	*/
	int XMLFile_load(const char* xmlFileName);
	/*
	* �����Ʋ��ҽڵ�
	* ����1�����ڵ㣨����ֵ��
	*/
	int get_root(TiXmlElement*& root);
	/*
	* ���ڵ��ѯ�ӽڵ����
	* ����1���ڵ���
	* ����2���ӽڵ�����������ֵ��
	*/
	int get_children_count(TiXmlElement* pRoot, int* count);
	/*
	* �����Ʋ��ҽڵ�
	* ����1���ڵ���
	* ����2���ڵ���
	* ����3���ڵ�ָ�루����ֵ��
	*/
	int _find_node(TiXmlElement* pRoot, const char* node_name, TiXmlElement*& pnode);
	/*
	* �����Ʋ��ҽڵ�
	* ����1���ڵ���
	* ����2���ڵ�ָ�루����ֵ��
	*/
	int find_node(const char* node_name, TiXmlElement*& pnode);
	/*
	* �����Ƽ�����ֵ���ҽڵ�
	* ����1�����ڵ㣨�����ã����ļ����ڵ㣩
	* ����2���ڵ���
	* ����3���ڵ����������ؼ����ԣ�
	* ����4���ڵ�����ֵ
	* ����5���ڵ�ָ�루����ֵ��
	*/
	int find_node_with_attribute(
		TiXmlElement* pRoot,
		const char* node_name,
		const char* attribute_name,
		const char* attribute_value,
		TiXmlElement*& pnode);

	/*
	* �����Ƽ�����ֵ���ҽڵ�
	* @param             �ڵ���
	* @param             �ڵ�������
	* @param             �ڵ�����ֵ
	* @param             �ڵ�ָ�루����ֵ��
	* @return �ɹ��ҵ�����0�� ���򷵻�-1
	*/
	int find_node_with_attribute(
		const char* node_name,
		const char* attribute_name,
		const char* attribute_value,
		TiXmlElement*& pnode
	);

	/*
	* ��XML�ļ��ж����ַ�������
	* ����1�����������ڵ�����
	* ����2������ֵ�������
	*/
	int get_str_para(const char* node_name, string& value);
	/*
	* ��XML�ļ��ж���double���Ͳ���
	* ����1�����������ڵ�����
	* ����2������ֵ�������
	*/
	int get_double_para(const char* node_name, double* value);
	/* ��xml�ļ��ж���double����
	* @param node_name                   ���ݽڵ���
	* @param Array                       ����
	* @param rootNode                    ���ڵ㣨Ĭ��ΪNULL�����ṩ���ڵ㣬���ڸ��ڵ�����������
	* @return �ɹ�����0�����򷵻�-1
	*/
	int getDoubleArray(const char* node_name, Mat& Array, TiXmlElement* rootNode = NULL);
	/*
	* ��XML�ļ��ж������Ͳ���
	* ����1�����������ڵ�����
	* ����2������ֵ�������
	*/
	int get_int_para(const char* node_name, int* value);
	/* ��xml�ļ��ж���int����
	* @param node_name                   ���ݽڵ���
	* @param Array                       ����
	* @param rootNode                    ���ڵ㣨Ĭ��ΪNULL�����ṩ���ڵ㣬���ڸ��ڵ�����������
	* @return �ɹ�����0�����򷵻�-1
	*/
	int getIntArray(const char* node_name, Mat& Array, TiXmlElement* rootNode = NULL);



	/*************************************************/
	/**********   Sensor-specific functions **********/
	/*************************************************/


	/*
	* ��TerraSAR-X GEOREF.xml�ļ��ж������Ƶ����
	* ����1�����Ƶ���������ֵ��N��6����ÿ�зֱ�Ϊ������γ���ߣ��У��У����ӽǣ�
	*/
	int get_gcps_from_TSX(Mat& gcps);
	/*
	* ��TerraSAR-X����XML�ļ��ж����������
	* ����1��������������ֵ��N��7����ÿ�зֱ��ǣ�GPSʱ�䣬λ�ã��ٶȣ�
	*/
	int get_stateVec_from_TSX(Mat& stateVec);
	/*
	* ��TerraSAR-X��xml�ļ��ж�������������Ƶ�ʲ�������ϵ��
	* ����1������������Ƶ�ʣ����ֵ�� N��(N_order+2)����NΪ���������Ĺ�������N_orderΪб���������������Ͻ���, �������������ϵ���Ͳο��������ʱ�䣩
	*/
	int get_dopplerCentroid_from_TSX(Mat& doppler);


	/*
	* ��sentinel1��������xml�ļ��ж���������Ƶ�����
	* ����1�����Ƶ����ݣ����ֵ��N��6����ÿ�зֱ�Ϊ������γ���ߣ��У��У����ӽǣ�
	*/
	int get_gcps_from_sentinel(Mat& gcps);
	/*
	* ��sentinel1��������xml�ļ��ж�������������Ƶ�ʲ���
	* ����1������������Ƶ�ʣ����ֵ�� N��(N_order+2)����NΪ���������Ĺ�������N_orderΪб���������������Ͻ���, �������������ϵ���Ͳο��������ʱ�䣩
	*/
	int get_dopplerCentroid_from_sentinel(Mat& doppler);
	/*
	* ��sentinel1��������xml�ļ��ж����������
	* ����1��������������ֵ��N��7����ÿ�зֱ��ǣ�GPSʱ�䣬λ�ã��ٶȣ�
	*/
	int get_stateVec_from_sentinel(Mat& stateVec);


private:
	char m_xmlFileName[2048];
	TiXmlDocument doc;
	int data_node_count;
	char error_head[256];


	
};



/**************************************************/
/*********           ��ʽת�����        **********/
/**************************************************/

class InSAR_API FormatConversion
{
public:
	FormatConversion();
	~FormatConversion();

	/*
	* ���ܣ����ַ�����ʽ��UTCʱ��ת��ΪGPSʱ��
	* ����1��UTCʱ��
	* ����2��GPSʱ��
	*/
	int utc2gps(const char* utc_time, double* gps_time);
	/** @brief �����µ�h5�ļ������ļ��Ѵ����򸲸ǣ�

	@param filename     �ļ���
	*/
	int creat_new_h5(const char* filename);
	/*@brief ���ܣ���h5�ļ���д�������
	* @param filename                �ļ���
	* @param dataset_name            dataset��
	* @param type                    �������ͣ�CV_8U/CV_16S/CV_32S/CV_32F/CV_64F��
	* @param rows                    dataset����
	* @param cols                    dataset����
	* @return �ɹ�����0�����򷵻�-1
	*/
	int write_zero_array_to_h5(const char* filename, const char* dataset_name, int type, int rows, int cols);
	/*
	* ���ܣ���h5�ļ���д��ʵ�����󣨸�����λ�����ϵ���ȣ�,input_array������16λ���ͻ���double/float��
	* ����1���ļ���
	* ����2��dataset��
	* ����3 ��д�����
	*/
	int write_array_to_h5(const char* filename, const char* dataset_name, const Mat& input_array);
	/*@brief ��h5�ļ���д��double������
	* @param h5File                     h5�ļ�
	* @param datasetName                ������
	* @param data                       double������
	* @return �ɹ�����0�����򷵻�-1
	*/
	int write_double_to_h5(
		const char* h5File,
		const char* datasetName,
		double data
	);
	/*@brief ��h5�ļ���д��int������
	* @param h5File                     h5�ļ�
	* @param datasetName                ������
	* @param data                       double������
	* @return �ɹ�����0�����򷵻�-1
	*/
	int write_int_to_h5(
		const char* h5File,
		const char* datasetName,
		int data
	);
	/*
	* ���ܣ���h5�ļ��ж���ʵ������(��������Ϊdouble�͡�16λ���ͻ���32λ����)
	* ����1���ļ���
	* ����2��dataset��
	* ����3���������
	*/
	int read_array_from_h5(const char* filename, const char* dataset_name, Mat& out_array);
	/*@brief ��h5�ļ��ж���double����
	* @param h5File                      h5�ļ�
	* @param datasetName                 ������
	* @param data                        ����
	* @return �ɹ�����0�����򷵻�-1
	*/
	int read_double_from_h5(
		const char* h5File,
		const char* datasetName,
		double* data
	);
	/*@brief ��h5�ļ��ж���int����
	* @param h5File                      h5�ļ�
	* @param datasetName                 ������
	* @param data                        ����
	* @return �ɹ�����0�����򷵻�-1
	*/
	int read_int_from_h5(
		const char* h5File,
		const char* datasetName,
		int* data
	);
	/*
	* ���ܣ���h5�ļ��ж�ȡ���������Ӽ�
	* ����1��h5�ļ���
	* ����2��dataset��
	* ����3����ƫ����(��0��ʼ)
	* ����4����ƫ��������0��ʼ��
	* ����5���Ӽ�����
	* ����6���Ӽ�����
	* ����7������Ӽ�����
	*/
	int read_subarray_from_h5(
		const char* filename,
		const char* dataset_name,
		int offset_row,
		int offset_col,
		int rows_subarray,
		int cols_subarray,
		Mat& out_array
	);
	/** @brief �����е�H5�ļ�ָ�����ݼ������е�ָ��λ��д���Ӿ���

	@param h5_filename                   h5�ļ���
	@param dataset_name                  ���ݼ�����
	@param subarray                      �Ӿ�������
	@param offset_row                    ��ƫ��������0��ʼ��
	@param offset_col                    ��ƫ��������0��ʼ��
	@param rows_subarray                 �Ӽ�����������
	@param cols_subarray                 �Ӽ�����������
	@return �ɹ�����0�� ���򷵻�-1
	*/
	int write_subarray_to_h5(
		const char* h5_filename,
		const char* dataset_name,
		Mat& subarray,
		int offset_row,
		int offset_col,
		int rows_subarray,
		int cols_subarray
	);
	/*
	* ���ܣ���h5�ļ�д���ַ�������
	* ����1���ļ���
	* ����2��dataset��
	* ����3����д���ַ�������
	*/
	int write_str_to_h5(const char* filename, const char* dataset_name, const char* str);
	/*
	* ���ܣ���h5�ļ��ж����ַ�������
	* ����1���ļ���
	* ����2��dataset��
	* ����3������ַ�������
	*/
	int read_str_from_h5(const char* filename, const char* dataset_name, string& string);
	/*
	* ���ܣ���h5�ļ�д�븴ͼ�����ݣ�SLC��������Ѿ�������д�롣
	* ����1���ļ���
	* ����2��������
	*/
	int write_slc_to_h5(const char* filename, const ComplexMat& slc);
	/*
	* ���ܣ���h5�ļ��ж���slc����
	* ����1���ļ���
	* ����2�����slc
	*/
	int read_slc_from_h5(const char* filename, ComplexMat& slc);


	/*------------------------------------------------*/
	/*            TerraSAR-X��Ʒ���ݵ��빤��          */
	/*------------------------------------------------*/

	/*
	* ��TerraSAR-X���ǵ�.cos�����ж���slc����(���ı����ͣ���Ȼ��16λ����)
	* ����1��.cos�ļ���
	* ����2�������ݾ������ֵ��
	*/
	int read_slc_from_TSXcos(const char* filename, ComplexMat& slc);
	/** @brief ��TerraSAR-X�������ݸ�ʽת��Ϊ�Զ����h5��ʽ

	@param cosar_filename                     TerraSAR-X .cos�ļ���
	@param xml_filename                       TerraSAR-X ��xml�ļ���
	@param GEOREF_filename                    TerraSAR-X GEOREF.xml�ļ���
	@param dst_h5_filename                    Ŀ��h5�ļ������ļ��Ѿ������򸲸ǣ�
	@return �ɹ�����0�����򷵻�-1
	*/
	int TSX2h5(
		const char* cosar_filename,
		const char* xml_filename,
		const char* GEOREF_filename,
		const char* dst_h5_filename
	);
	/** @brief ��TerraSAR-X�������ݸ�ʽת��Ϊ�Զ����h5��ʽ

	@param xml_filename                       TerraSAR-X ��xml�ļ���
	@param dst_h5_filename                    Ŀ��h5�ļ�
	@return �ɹ�����0�����򷵻�-1
	*/
	int TSX2h5(
		const char* xml_filename,
		const char* dst_h5_filename
	);
	/** @brief ��TerraSAR-X�������ݸ�ʽת��Ϊ�Զ����h5��ʽ(������ѡ��)

	@param xml_filename                       TerraSAR-X ��xml�ļ���
	@param dst_h5_filename                    Ŀ��h5�ļ�
	@param polarization                       ������ʽ(Ĭ��ΪHH����)
	@return �ɹ�����0�����򷵻�-1
	*/
	int TSX2h5(
		const char* xml_filename,
		const char* dst_h5_filename,
		const char* polarization ="HH"
	);





	/*------------------------------------------------*/
	/*            Sentinel1��Ʒ���ݵ��빤��           */
	/*------------------------------------------------*/

	/*
	* ��sentinel1���Ǿ��ܹ�������ļ��ж������ܹ������
	* ����1�����ܹ�������ļ�
	* ����2���ֹ��������ʼʱ��
	* ����3���ֹ�����ݽ���ʱ��
	* ����4��Ŀ��h5�ļ�
	*/
	int read_POD(const char* POD_filename, double start_time, double stop_time, const char* dst_h5_filename);
	/** @brief ��sentinel1���������ж���slc���ݣ�������������Ϊ16λ���ͣ�
	* 
	* @param filename                    sentinel1���������ļ���
	* @param xml_filename                xml�����ļ�
	* @param slc                         �����󣨶�����slc���ݣ�
	* @param gcps_line                   deburst֮����Ƶ������꣨int�ͣ�1��n��
	* @return �ɹ�����0�����򷵻�-1
	*/
	int read_slc_from_Sentinel(const char* filename, const char* xml_filename, ComplexMat& slc, Mat& gcps_line);
	/*
	* ���ܣ�sentinel1����deburst(��������Ϊ16λ����)
	* ����1������deburst��xml�����ļ�
	* ����2��������slc���ݣ�ԭ�ز�����
	* ����3����Ч�л��۱�־����(CV_32S��)
	*/
	int sentinel_deburst(const char* xml_filename, ComplexMat& slc, Mat& sentinel);
	/*
	* ��sentinel1�������ݸ�ʽת��Ϊ�Զ����h5��ʽ
	* ����1��tiff��ʽ�ļ���������SLCͼ��
	* ����2��xml�ļ���
	* ����3��Ŀ��h5�ļ���
	* ����4�����ܹ�������ļ�
	*/
	int sentinel2h5(
		const char* tiff_filename,
		const char* xml_filename,
		const char* dst_h5_filename,
		const char* POD_file = NULL
	);
	/** ����sentinel����������h5�ļ���
	* @param manifest                            sentinel��������manifest�ļ�
	* @param subswath_name                       sentinel����IWģʽ��Ϊ��iw1/iw2/iw3��
	* @param polarization                        ������ʽ��vv/vh��
	* @param dest_h5_file                        Ŀ��h5�ļ�
	* @param PODFile                             ���������ļ�
	* @return �ɹ�����0�����򷵻�-1
	*/
	int import_sentinel(
		const char* manifest,
		const char* subswath_name,
		const char* polarization,
		const char* dest_h5_file,
		const char* PODFile = NULL
	);
	/** @brief ����һ��burst����
	* 
	* @param pnode                         burst�ڵ���Ϣ
	* @param xmldoc                        xml�ṹ��
	* @param fp                            ͼ���ļ�ָ��
	* @param linesPerBurst                 ÿ��burst��������
	* @param samplesPerBurst               ÿ�����ݵ���
	* @param burst                         ������burst����
	* @return �ɹ�����0�����򷵻�-1������-1���Զ��ر��ļ�ָ�룩
	*/
	int get_a_burst(
		TiXmlElement* pnode,
		XMLFile& xmldoc,
		FILE*& fp,
		int linesPerBurst,
		int samplesPerBurst,
		ComplexMat& burst
	);
	/** @brief ����һ��burst���ݣ�����������һ��burst֮����ص������С��
	*
	* @param burst_num                         burst���
	* @param xml_file                          xml�ļ�
	* @param tiff_file                         tiff�����ļ�
	* @param burst                             burst����
	* @param overlapSize                       �ص�����ߴ磨��λ��
	*/
	int get_burst_sentinel(
		int burst_num,
		const char* xml_file,
		const char* tiff_file,
		ComplexMat& burst,
		int* overlapSize
	);
	/** @brief ����burst֮����ص�����ߴ�
	* 
	* @param last_burst                      ��һ��burst
	* @param this_burst                      �������ص�����ߴ��burst
	* @param overlapSize                     �ص�����ߴ�
	* @return �ɹ�����0�����򷵻�-1
	*/
	int deburst_overlapSize(
		ComplexMat& last_burst,
		ComplexMat& this_burst,
		int* overlapSize
	);
	/** @brief burst֮�����ƴ�ӣ���src_burstƴ�ӵ�dst_burst�ϣ�
	* 
	* @param src_burst                 ��ƴ��burst
	* @param dst_burst                 ƴ��burst
	* @param stitch_type               ��Ϸ�ʽ��low/mid/high��
	* @param overlapSize               �ص�����ߴ�
	* @return �ɹ�����0�����򷵻�-1
	*/
	int burst_stitch(
		ComplexMat& src_burst,
		ComplexMat& dst_burst,
		int overlapSize,
		const char* stitch_type = "mid"
	);



	/*------------------------------------------------*/
	/*            ALOS1/2��Ʒ���ݵ��빤��             */
	/*------------------------------------------------*/

	/*
	* ��ALOS1/2 CEOS��ʽLevel-1.1��Ʒ�ж�ȡslc����(float��)
	* ����1��ͼ���ļ�
	* ����2��slc����
	*/
	int read_slc_from_ALOS(const char* img_file, ComplexMat& slc);
	/*
	* ��ALOS1/2 CEOS��ʽLevel-1.1��Ʒ�ж�ȡ���ǹ������
	* ����1��ALOS LED�ļ�
	* ����2���������
	*/
	int read_stateVec_from_ALOS(const char* LED_file, Mat& stateVec);
	/*
	* ��ALOS1/2 CEOS��ʽLevel-1.1��Ʒ�ж�ȡ��γ������ͼ������֮���ת����ϵϵ��
	* ����1��ALOS LED�ļ�
	* ����2��ͼ�����꣨�С��У��뾭��֮���ת����ϵ������-->���ȣ�
	* ����3��ͼ�����꣨�С��У���γ��֮���ת����ϵ������-->γ�ȣ�
	* ����4����γ����������֮���ת����ϵ����γ��-->������
	* ����5����γ����������֮���ת����ϵ����γ��-->������
	*/
	int read_conversion_coefficient_from_ALOS(
		const char* LED_file,
		Mat& lon_coefficient,
		Mat& lat_coefficient,
		Mat& row_coefficient,
		Mat& col_coefficient
	);
	/*
	* ��ALOS1/2 CEOS��ʽLevel-1.1��Ʒ���ݶ������Զ����hdf5�ļ���
	* ����1��ALOS IMG�ļ�
	* ����2��ALOS LED�ļ�
	* ����3���Զ���h5�ļ�
	*/
	int ALOS2h5(const char* IMG_file, const char* LED_file, const char* dst_h5);
	/** @brief ��ԭh5�ļ��еĲ�����Ϣ��������һ��h5��
	
    @param Input_file        ԭʼh5�ļ�
	@param Output_file       ���h5�ļ�
	*/
	int Copy_para_from_h5_2_h5(const char* Input_file, const char* Output_file);

	/*------------------------------------------------*/
	/*               GEDI��Ʒ���ݵ��빤��             */
	/*------------------------------------------------*/

	/** @brief ��GEDI L2B����Ʒ�ж�ȡDSM��DTM�Լ������������Ϣ
	* @param gedi_h5_file                        GEDI L2B����Ʒ�ļ���HDF5��ʽ��
	* @param rh100                               rh100����
	* @param elev_lowestmode                     ���µ��β�����DTM��
	* @param elev_highestreturn                  �ڲ�߶���Ϣ��DSM��
	* @param lon                                 ������Ϣ
	* @param lat                                 γ����Ϣ
	* @param dem                                 TanDEM-X 90m �߳���Ϣ
	* @param quality_index                       ������Ϣ
	* @return �ɹ�����0�����򷵻�-1
	*/
	int read_height_metric_from_GEDI_L2B(const char* gedi_h5_file, Mat& rh100, Mat& elev_lowestmode, Mat& elev_highestreturn, Mat& lon, Mat& lat, Mat& dem, Mat& quality_index);


private:
	char error_head[256];
	char parallel_error_head[256];

};

struct BurstIndices
{
	int firstBurstIndex;
	int secondBurstIndex;
	bool inUpperPartOfFirstBurst;
	bool inUpperPartOfSecondBurst;
	/*Ĭ�Ϲ��캯��*/
	BurstIndices()
	{
		firstBurstIndex = secondBurstIndex = -1;
		inUpperPartOfFirstBurst = inUpperPartOfSecondBurst = false;
	}
	/*�������캯��*/
	BurstIndices(const BurstIndices& cp)
	{
		this->firstBurstIndex = cp.firstBurstIndex;
		this->inUpperPartOfFirstBurst = cp.inUpperPartOfFirstBurst;
		this->inUpperPartOfSecondBurst = cp.inUpperPartOfSecondBurst;
		this->secondBurstIndex = cp.secondBurstIndex;
	}
	/*��ֵ����*/
	BurstIndices operator=(const BurstIndices& cp)
	{
		this->firstBurstIndex = cp.firstBurstIndex;
		this->inUpperPartOfFirstBurst = cp.inUpperPartOfFirstBurst;
		this->inUpperPartOfSecondBurst = cp.inUpperPartOfSecondBurst;
		this->secondBurstIndex = cp.secondBurstIndex;
		return *this;
	}
};

/*---------------------------------------*/
/*              ���ָ߳�ģ��             */
/*---------------------------------------*/
class InSAR_API DigitalElevationModel
{
public:
	DigitalElevationModel();
	~DigitalElevationModel();
	/*@brief ����SRTM�߳��ļ���
	* @param lonMin                       ��С����
	* @param lonMax                       ��󾭶�
	* @param latMin                       ��Сγ��
	* @param latMax                       ���γ��
	* @param name                         �ļ���
	* @return �ɹ�����0�����򷵻�-1
	*/
	int getSRTMFileName(
		double lonMin,
		double lonMax,
		double latMin,
		double latMax,
		vector<string>& name
	);
	/*@brief ����SRTM�߳�����
	* @param name                         �ļ���
	* @return �ɹ�����0�����򷵻�-1
	*/
	int downloadSRTM(const char* name);
	/*@brief ��ȡ���ָ߳�ģ��
	* @param filepath                     �ļ�·��
	* @param lonMin                       ��С����
	* @param lonMax                       ��󾭶�
	* @param latMin                       ��Сγ��
	* @param latMax                       ���γ��
	* @return �ɹ�����0�����򷵻�-1
	*/
	int getRawDEM(
		const char* filepath,
		double lonMin,
		double lonMax,
		double latMin,
		double latMax
	);
	/*@brief ���ݾ�γ�Ȼ�ȡ�߳�(ƽ����ֵ��)
	* @param lon                          ����
	* @param lat                          γ��
	* @param elevation                    �߶�
	* @return �ɹ�����0�����򷵻�-1
	*/
	int getElevation(
		double lon,
		double lat,
		double* elevation
	);
	/*@brief ��ȡSRTM�е�geotiff�߳�����
	* @param geotiffFile                  geotiff�ļ�
	* @param outDEM                       ������DEM����
	* @return �ɹ�����0�����򷵻�-1
	*/
	static int geotiffread(
		const char* geotiffFile,
		Mat& outDEM
	);
	/*@brief ��ѹ�ļ���ָ���ļ���
	* @param srcFile                      ����ѹѹ���ļ�
	* @param dstPath                      Ŀ���ļ���
	* @return �ɹ�����0�����򷵻�-1
	*/
	static int unzip(const char* srcFile, const char* dstPath);

public:
	/*DEM���ݣ��߳�Ϊshort�����ݣ�*/
	Mat rawDEM;
	/*DEM��������*/
	int rows;
	/*DEM��������*/
	int cols;
	/*���ϽǾ���*/
	double lonUpperLeft;
	/*���Ͻ�γ��*/
	double latUpperLeft;
	/*���½Ǿ���*/
	double lonLowerRight;
	/*���½�γ��*/
	double latLowerRight;
	/*DEM���Ȳ������*/
	double lonSpacing;
	/*DEMγ�Ȳ������*/
	double latSpacing;
	/*DEM·��*/
	string DEMPath;
	/*SRTMȫ��߳�url*/
	string SRTMURL = "http://srtm.csi.cgiar.org/wp-content/uploads/files/srtm_5x5/TIFF/";

	char error_head[512];

};



/*--------------------------------------*/
/*              ���ǹ������            */
/*--------------------------------------*/
class InSAR_API orbitStateVectors
{
public:
	orbitStateVectors(Mat& stateVectors, double startTime, double stopTime);
	orbitStateVectors(Mat& stateVectors, double startTime, double stopTime, double delta_time);
	~orbitStateVectors();
	/*@brief ���ó���������ʼ��ֹʱ��
	* @param startTime
	* @param stopTime
	* @return �ɹ�����0�����򷵻�-1
	*/
	int setSceneStartStopTime(double startTime, double stopTime);
	/*@brief ��ȡ������ʼʱ��
	* @return ����������ʼʱ��
	*/
	double get_start_time();
	/*@brief ��ȡ�������ʱ��
	* @return �����������ʱ��
	*/
	double get_stop_time();
	/*@brief ��ȡ������άλ����Ϣ���������ղ�ֵ��
	* @param azimuthTime                   ��λ��ʱ��
	* @param position                      ������άλ��
	* @return �ɹ�����0�����򷵻�-1
	*/
	int getPosition(double azimuthTime, Position& position);
	/*@brief ��ȡ������ά�ٶ���Ϣ���������ղ�ֵ��
	* @param azimuthTime                   ��λ��ʱ��
	* @param velocity                      ������ά�ٶ�
	* @return �ɹ�����0�����򷵻�-1
	*/
	int getVelocity(double azimuthTime, Velocity& velocity);
	/*@brief ���ݷ�λ��ʱ���ȡstatevector������ʽ��ֵ��
	* @param time                          ��λ��ʱ��
	* @param osv                           �����Ϣ
	* @return �ɹ�����0�����򷵻�-1
	*/
	int getOrbitData(double time, OSV* osv);
	/*@brief ���¹����Ϣ
	* @return �ɹ�����0�����򷵻�-1
	*/
	int applyOrbit();

public:
	Mat stateVectors;
	Mat newStateVectors;
private:
	
	int nv = 10;
	double dt;
	int polyDegree = 3;
	double startTime;
	double stopTime;
	/*�����Ϣ�Ƿ��Ѹ���*/
	bool isOrbitUpdated;
};


/*------------------------------------------------*/
/*             COSMO-SkyMed���ݶ�ȡ����           */
/*------------------------------------------------*/
class InSAR_API CSK_reader
{
public:
	CSK_reader(const char* csk_data_file);
	~CSK_reader();
	/*@brief ��ʼ��
	* @param csk_data_file                    COSMO-SkyMedԴhdf5�����ļ�
	* @return �ɹ�����0�����򷵻�-1
	*/
	int init();
	
	/*@brief ������д�뵽ָ��h5�ļ�
	* @param dst_h5                          ָ��hdf5�ļ�
	* @return �ɹ�����0�����򷵻�-1
	*/
	int write_to_h5(
		const char* dst_h5
	);

private:

	/*@brief ��COSMO-SkyMedԴhdf5����L1A��Ʒ�ж�ȡ����
	* @param CSK_data_file                    COSMO-SkyMedԴhdf5�����ļ�
	* @return �ɹ�����0�����򷵻�-1
	*/
	int read_data(
		const char* CSK_data_file
	);
	/*@brief ��COSMO-SkyMedԴhdf5����L1A��Ʒ�ж�ȡ���Ӹ�ͼ��
	* @param CSK_data_file                    COSMO-SkyMedԴhdf5�����ļ�
	* @param slc                              �����ĵ��Ӹ����ݾ���
	* @return �ɹ�����0�����򷵻�-1
	*/

	int read_slc(
		const char* CSK_data_file,
		ComplexMat& slc
	);
	/*@brief ��hdf5�ļ���ȡstring��������
	* @param object_id                       ��Ӧ��object
	* @param attribute_name                  string������
	* @param attribute_value                 string����ֵ������ֵ��
	* @return �ɹ�����0�����򷵻�-1
	*/
	int get_str_attribute(
		hid_t object_id,
		const char* attribute_name,
		string& attribute_value
	);
	/*@brief ��hdf5�ļ���ȡ������������
	* @param object_id                       ��Ӧ��object
	* @param attribute_name                  ������
	* @param attribute_value                 ����ֵ������ֵ��
	* @return �ɹ�����0�����򷵻�-1
	*/
	int get_array_attribute(
		hid_t object_id,
		const char* attribute_name,
		Mat& attribute_value
	);

private:
	string csk_data_file;
	bool b_initialized;
	string acquisition_start_time;
	string acquisition_stop_time;
	double azimuth_resolution;
	double azimuth_spacing;
	double carrier_frequency;
	double prf;
	double range_resolution;
	double range_spacing;
	double slant_range_first_pixel;
	double slant_range_last_pixel;
	Mat topleft, topright, bottomleft, bottomright;
	Mat state_vec, inc_coefficient, lon_coefficient, lat_coefficient, row_coefficient, col_coefficient;
	string lookside;
	string sensor;
	string polarization, orbit_direction;
	ComplexMat slc;

};

/*------------------------------------------------*/
/*               �����ͼ���ݶ�ȡ����             */
/*------------------------------------------------*/
class InSAR_API HTHT_reader
{
public:
	HTHT_reader(const char* data_file, const char* xml_file, int mode = 0);//mode=0Ϊ����ģʽ,mode=1Ϊ���Ǹ���ģʽ
	~HTHT_reader();
	/*@brief ��ʼ��
	* @return �ɹ�����0�����򷵻�-1
	*/
	int init();

	/*@brief ������д�뵽ָ��h5�ļ�
	* @param dst_h5                          ָ��hdf5�ļ�
	* @return �ɹ�����0�����򷵻�-1
	*/
	int write_to_h5(
		const char* dst_h5
	);

private:

	/*@brief �Ӻ�ͼL1��Ʒ�ж�ȡ����
	@param xml_file                    ��ͼxml�����ļ���.xml��
	@param data_file                   ��ͼxml�����ļ���.tiff��
	@return �ɹ�����0�����򷵻�-1
	*/
	int read_data(
		const char* xml_file,
		const char* data_file
	);
	/*@brief �Ӻ�ͼ����L1��Ʒ�ж�ȡ���Ӹ�ͼ��
	* @param data_file                        ��ͼͼ�������ļ���.tiff��
	* @param slc                              �����ĵ��Ӹ����ݾ���
	* @return �ɹ�����0�����򷵻�-1
	*/

	int read_slc(
		const char* data_file,
		ComplexMat& slc
	);
private:
	string HT_data_file, HT_xml_file;
	bool b_initialized;
	string acquisition_start_time;
	string acquisition_stop_time;
	double azimuth_resolution;
	double azimuth_spacing;
	double carrier_frequency;
	double inc_center;
	double prf;
	double range_resolution;
	double range_spacing;
	double slant_range_first_pixel;
	double slant_range_last_pixel;
	double topleft_lon, topright_lon, bottomleft_lon, bottomright_lon,
		topleft_lat, topright_lat, bottomleft_lat, bottomright_lat;
	Mat state_vec;
	string sensor;
	ComplexMat slc;
	int mode = 0;

};

/*------------------------------------------------*/
/*               ½̽1�����ݶ�ȡ����              */
/*------------------------------------------------*/
class InSAR_API LUTAN_reader
{
public:
	LUTAN_reader(const char* data_file, const char* xml_file, int mode = 1);//mode=1Ϊ����ģʽ,mode=2Ϊ˫�Ǹ���ģʽ
	~LUTAN_reader();
	/*@brief ��ʼ��
	* @return �ɹ�����0�����򷵻�-1
	*/
	int init();

	/*@brief ������д�뵽ָ��h5�ļ�
	* @param dst_h5                          ָ��hdf5�ļ�
	* @return �ɹ�����0�����򷵻�-1
	*/
	int write_to_h5(
		const char* dst_h5
	);

private:

	/*@brief ��½̽һ��L1��Ʒ�ж�ȡ����
	@param xml_file                    ½̽һ��xml�����ļ���.xml��
	@param data_file                   ½̽һ��xml�����ļ���.tiff��
	@return �ɹ�����0�����򷵻�-1
	*/
	int read_data(
		const char* xml_file,
		const char* data_file
	);
	/*@brief ��½̽һ��L1��Ʒ�ж�ȡ���Ӹ�ͼ��
	* @param data_file                        ½̽һ��ͼ�������ļ���.tiff��
	* @param slc                              �����ĵ��Ӹ����ݾ���
	* @return �ɹ�����0�����򷵻�-1
	*/

	int read_slc(
		const char* data_file,
		ComplexMat& slc
	);
private:
	string LT_data_file, LT_xml_file;
	bool b_initialized;
	string acquisition_start_time;
	string acquisition_stop_time;
	double azimuth_resolution;
	double azimuth_spacing;
	double carrier_frequency;
	double inc_center;
	double prf;
	double range_resolution;
	double range_spacing;
	double slant_range_first_pixel;
	double slant_range_last_pixel;
	double topleft_lon, topright_lon, bottomleft_lon, bottomright_lon,
		topleft_lat, topright_lat, bottomleft_lat, bottomright_lat;
	Mat state_vec;
	string sensor;
	ComplexMat slc;
	int mode = 1;

};



/*------------------------------------------------*/
/*             ���Ǹ���һ�����ݶ�ȡ����           */
/*------------------------------------------------*/
class InSAR_API Spacety_reader
{
public:
	Spacety_reader(const char* data_file, const char* xml_file);
	~Spacety_reader();
	/*@brief ��ʼ��
	* @return �ɹ�����0�����򷵻�-1
	*/
	int init();
	/*@brief ��ʼ��������ģʽ���ݲ����ã�
	* @return �ɹ�����0�����򷵻�-1
	*/
	int init_test();

	/*@brief ������д�뵽ָ��h5�ļ�
	* @param dst_h5                          ָ��hdf5�ļ�
	* @return �ɹ�����0�����򷵻�-1
	*/
	int write_to_h5(
		const char* dst_h5
	);

private:

	/*@brief ������L1��Ʒ�ж�ȡ����
	@param xml_file                    ����xml�����ļ���.xml��
	@param data_file                   ����xml�����ļ���.tiff��
	@return �ɹ�����0�����򷵻�-1
	*/
	int read_data(
		const char* xml_file,
		const char* data_file
	);
	/*@brief ������L1��Ʒ�ж�ȡ���ݣ�����ģʽ���ݲ����ã�
	@param xml_file                    ����xml�����ļ���.xml��
	@param data_file                   ����xml�����ļ���.tiff��
	@return �ɹ�����0�����򷵻�-1
	*/
	int read_data_test(
		const char* xml_file,
		const char* data_file
	);
	/*@brief ����������L1��Ʒ�ж�ȡ���Ӹ�ͼ��
	* @param data_file                        ����ͼ�������ļ���.tiff��
	* @param slc                              �����ĵ��Ӹ����ݾ���
	* @return �ɹ�����0�����򷵻�-1
	*/

	int read_slc(
		const char* data_file,
		ComplexMat& slc
	);
private:
	string Spacety_data_file, Spacety_xml_file;
	bool b_initialized;
	string acquisition_start_time;
	string acquisition_stop_time;
	double azimuth_resolution;
	double azimuth_spacing;
	double carrier_frequency;
	double inc_center;
	double prf;
	double range_resolution;
	double range_spacing;
	double slant_range_first_pixel;
	double slant_range_last_pixel;
	double topleft_lon, topright_lon, bottomleft_lon, bottomright_lon,
		topleft_lat, topright_lat, bottomleft_lat, bottomright_lat;
	Mat state_vec;
	string sensor;
	ComplexMat slc;

};

/*------------------------------------------------*/
/*               �ڱ�һ�����ݶ�ȡ����             */
/*------------------------------------------------*/
class InSAR_API Sentinel1Reader
{
public:
	Sentinel1Reader();
	Sentinel1Reader(const char* xmlfile, const char* tiffFile, const char* PODFile = NULL);
	~Sentinel1Reader();
	/* ����xml�ļ�
	* @param xmlfile            xml�ļ�
	* @param tiffFile           tiff�ļ�
	* @return �ɹ�����0�����򷵻�-1
	*/
	int load(const char* xmlfile, const char* tiffFile);
	/* ��ȡ����������Ƶ�ʹ�������
	* @param dcEstimateList               ����������Ƶ�ʹ������ݣ�count��5��
	* @return �ɹ�����0�����򷵻�-1
	*/
	int getDcEstimateList();
	/* ��ȡ�����յ�Ƶ������
	* @return �ɹ�����0�����򷵻�-1
	*/
	int getAzimuthFmRateList();
	/* ��ȡantennaPattern����
	* @param antennaPattern_slantRangeTime
	* @param antennaPattern_elevationAngle
	* @return �ɹ�����0�����򷵻�-1
	*/
	int getAntennaPattern();
	/* @brief ��ȡburst����
	* @param burstCount                 burst����
	* @return �ɹ�����0�����򷵻�-1
	*/
	int getBurstCount(int* burstCount);
	/*@brief ��ȡÿ��burst��һ�з�λ��ʱ��
	* @return �ɹ�����0�� ���򷵻�-1
	*/
	int getBurstAzimuthTime();
	/*@brief ��ȡÿ��burstÿ�е�һ����Ч��������
	* @return �ɹ�����0�����򷵻�-1
	*/
	int getFirstValidSample();
	/*@brief ��ȡÿ��burstÿ�����һ����Ч��������
	* @param firstValidSample                        ÿ��burstÿ�����һ����Ч��������(burstCount��1)
	* @return �ɹ�����0�����򷵻�-1
	*/
	int getLastValidSample();
	/*@brief ��ȡÿ��burst��һ����Ч��������
	* @param firstValidLine                          ÿ��burst��һ����Ч��������(burstCount��1)
	* @return �ɹ�����0�����򷵻�-1
	*/
	int getFirstValidLine();
	/*@brief ��ȡÿ��burst���һ����Ч��������
	* @param lastValidLine                           ÿ��burst���һ����Ч��������(burstCount��1)
	* @return �ɹ�����0�����򷵻�-1
	*/
	int getLastValidLine();
	/*@brief ��ȡ������Ƶ���Ϣ
	* @param geolocationGridPoint                    ������Ƶ�(n��6����/γ/��/��/��/���ӽ�)
	* @return �ɹ�����0�����򷵻�-1
	*/
	int getGeolocationGridPoint();
	/*@brief ���¿��Ƶ���Ϣ
	* @return �ɹ�����0�����򷵻�-1
	*/
	int updateGeolocationGridPoint();
	/*@brief ���ݿ��Ƶ�������Ͼ�γ�ȡ����ӽ����������꣨�С��У�֮��Ķ���ʽ��ϵ
	* @return �ɹ�����0�����򷵻�-1
	*/
	int fitCoordinateConversionCoefficient();
	/*@brief ��ȡ�����Ϣ
	* @return �ɹ�����0�����򷵻�-1
	*/
	int getOrbitList();
	/*@brief ��ȡ���ܹ������
	* @param POD_file                                ���ܹ�������ļ�
	* @return �ɹ�����0�����򷵻�-1
	*/
	int getPOD(const char* POD_file);
	/*@brief ��ȡ��������
	* @return �ɹ�����0�����򷵻�-1
	*/
	int getOtherParameters();

	/*@brief ׼������
	* @param PODFile                                  ���ܹ�������ļ�
	* @return �ɹ�����0�����򷵻�-1
	*/
	int prepareData(const char* PODFile = NULL);
	/*@brief ��TIFF�ļ��ж�����ͼ������
	* @param slc                                     ��ͼ������
	* @return �ɹ�����0�����򷵻�-1
	*/
	int getSLC(ComplexMat& slc);
	/*@brief ������д��h5�ļ�
	* @param h5File                                  Ŀ��h5�ļ�(Ĭ��ΪNULL)
	* @return �ɹ�����0�����򷵻�-1
	*/
	int writeToh5(
		const char* h5File
	);

private:

	/*��λ��ʱ����*/
	double azimuthTimeInterval;
	/*��λ��������*/
	double azimuthPixelSpacing;
	/*�����������*/
	double rangeSamplingRate;
	/*������������*/
	double rangePixelSpacing;
	/*�״���Ƶ*/
	double radarFrequency;
	/*��λ��ɨƵ��*/
	double azimuthSteeringRate;
	/*���б��ʱ��*/
	double slantRangeTime;
	/*Heading*/
	double headingAngle;
	/*�������ӽ�*/
	double incidence_center;
	/*��������*/
	int numberOfLines;
	/*��������*/
	int numberOfSamples;
	/*ÿ��burst����*/
	int linesPerBurst;
	/*burst����*/
	int burstCount;

	/*���ǣ��״����*/
	string sensor;
	/*������ʽ*/
	string polarization;
	/*�Ӵ�����*/
	string swath;
	/*������*/
	string pass;
	/*������ʼUTCʱ��*/
	string startTime;
	/*�������UTCʱ��*/
	string stopTime;
	



	/*��λ���Ƶ�ʹ�������*/
	Mat AzimuthFmRateList;
	/*����������Ƶ�ʹ�������*/
	Mat DcEstimateList;
	/*ÿ��burst��һ�з�λ��ʱ��*/
	Mat burstAzimuthTime;
	/*ÿ��burstÿ�е�һ����Ч��������*/
	Mat firstValidSample;
	/*ÿ��burstÿ�����һ����Ч��������*/
	Mat lastValidSample;
	/*ÿ��burst��һ����Ч��������*/
	Mat firstValidLine;
	/*ÿ��burst���һ����Ч��������*/
	Mat lastValidLine;
	/*���ԭʼ����*/
	Mat orbitList;
	/*����ԭʼ�������*/
	Mat preciseOrbitList;
	/*antennaPattern_slantRangeTime*/
	Mat antennaPattern_slantRangeTime;
	/*antennaPattern_elevationAngle*/
	Mat antennaPattern_elevationAngle;
	/*������Ƶ�*/
	Mat geolocationGridPoint;


	/*�������ϵ��*/
	Mat lon_coefficient;
	/*γ�����ϵ��*/
	Mat lat_coefficient;
	/*���������ϵ��*/
	Mat row_coefficient;
	/*���������ϵ��*/
	Mat col_coefficient;
	/*���ӽ����ϵ��*/
	Mat inc_coefficient;


	/*tiff�ļ�*/
	string tiffFile;
	/*���ܹ�������ļ�*/
	string PODFile;
	bool isDataAvailable;
	XMLFile xmldoc;
	bool bXmlLoad;
	char m_xmlFileName[2048];
	char error_head[256];
};




/*------------------------------------------------*/
/*                �ڱ�һ�ż��㹤��                */
/*------------------------------------------------*/
class InSAR_API Sentinel1Utils
{
public:
	/*@brief Ĭ�Ϲ��캯��
	*/
	Sentinel1Utils(const char* h5File);
	~Sentinel1Utils();
	/*@brief ��ʼ��
	* @return �ɹ�����0�����򷵻�-1
	*/
	int init();
	/*@brief ����ÿ��burst�ķ�λ��ο�ʱ��
	* @return �ɹ�����0�����򷵻�-1
	*/
	int computeReferenceTime();
	/*@brief ����ÿ��burst�ķ�λ������յ�Ƶ��
	* @return �ɹ�����0�����򷵻�-1
	*/
	int computeRangeDependDopplerRate();
	/*@brief ����ÿ��burst�ķ�λ�����������Ƶ��
	* @return �ɹ�����0�����򷵻�-1
	*/
	int computeDopplerCentroid();
	/*@brief ����ÿ��burst���ܶ������ʣ���Ƶ�ʼ�ɨƵ�ʣ�
	* @return �ɹ�����0�����򷵻�-1
	*/
	int computeDopplerRate();
	/*@brief ����burst���ݵ�ȥб��λ��ȥģ��λ
	* @param burstIndex                           burst���
	* @param derampDemodPhase                     ȥбȥģ��λ
	* @return �ɹ�����0�����򷵻�-1
	*/
	int computeDerampDemodPhase(
		int burstIndex,
		Mat& derampDemodPhase
	);
	/*@brief ��h5�ļ��ж���һ��burst������
	* @param burstIndex                          burst���
	* @param burstSLC                            һ��burst�ĸ�����
	* @return �ɹ�����0�����򷵻�-1
	*/
	int getBurst(
		int burstIndex,
		ComplexMat& burstSLC
	);



	/*@brief ���������Ƶ��
	* @param groundPosition                       �����λ��
	* @param satellitePosition                    ����λ��
	* @param satelliteVelocity                    �����ٶ�
	* @param dopplerFrequency                     ������Ƶ�ʣ�����ֵ��
	* @return �ɹ�����0�����򷵻�-1
	*/
	int getDopplerFrequency(
		Position groundPosition,
		Position satellitePosition,
		Velocity satelliteVelocity,
		double* dopplerFrequency
	);
	/*@brief ���������Ӧ��������շ�λ��ʱ��
	* @param groundPosition                       �����λ��
	* @param zeroDopplerTime                      ������շ�λ��ʱ��
	* @param dopplerFrequency                     ������Ƶ��(Ĭ��Ϊ0)
	* @return �ɹ�����0�����򷵻�-1
	*/
	int getZeroDopplerTime(
		Position groundPosition,
		double* zeroDopplerTime,
		double dopplerFrequency = 0.0
	);
	/*@brief ��������ͶӰ��SARͼ������ϵ�µľ�����ͷ�λ������
	* @param burstIndex                           burst���
	* @param groundPosition                       �����λ��
	* @param rangeIndex                           ����������
	* @param azimuthIndex                         ��λ������
	* @return �ɹ�����0�����򷵻�-1
	*/
	int getRgAzPosition(
		int burstIndex,
		Position groundPosition,
		double* rangeIndex,
		double* azimuthIndex
	);
	/*@brief ����������Ƿ�λ��ʱ��͵����λ��ʱ��б��
	* @param azimuthTime                         ��λ��ʱ��
	* @param groundPosition                      �����λ��
	* @param slantRange                          б��
	* @return �ɹ�����0�����򷵻�-1
	*/
	int getSlantRange(
		double azimuthTime,
		Position groundPosition,
		double* slantRange
	);
	/*@brief ��ȡ�����Ŀ������burst��Ϣ
	* @param groundPosition                      �����Ŀ��
	* @param burstIndice                         burst��Ϣ
	* @return �ɹ�����0�����򷵻�-1
	*/
	int getBurstIndice(
		Position groundPosition,
		BurstIndices& burstIndice
	);
	/*@brief ���㳡������λ�ã���γ�ȣ��߽�
	* @param lonMin                           ��С����
	* @param lonMax                           ��󾭶�
	* @param latMin                           ��Сγ��
	* @param latMax                           ���γ��
	* @return �ɹ�����0�����򷵻�-1
	*/
	int computeImageGeoBoundry(
		double* lonMin,
		double* lonMax,
		double* latMin,
		double* latMax
	);
	/*@brief ���㳡������λ�ã���γ�ȣ��߽�
	* @param lonMin                           ��С����
	* @param lonMax                           ��󾭶�
	* @param latMin                           ��Сγ��
	* @param latMax                           ���γ��
	* @param burstIndex                       burst��ţ�1-based��
	* @return �ɹ�����0�����򷵻�-1
	*/
	int computeImageGeoBoundry(
		double* lonMin,
		double* lonMax,
		double* latMin,
		double* latMax,
		int burstIndex
	);
	/*@brief burstƴ��
	* @param outFile                          deburst���h5�ļ�
	* @return �ɹ�����0�����򷵻�-1
	*/
	int deburst(const char* outFile);
public:

	/*��λ��ʱ����*/
	double azimuthTimeInterval;
	/*��λ��������*/
	double azimuthPixelSpacing;
	/*�����������*/
	double rangeSamplingRate;
	/*������������*/
	double rangePixelSpacing;
	/*�״���Ƶ*/
	double radarFrequency;
	/*��λ��ɨƵ��*/
	double azimuthSteeringRate;
	/*���б��ʱ��*/
	double slantRangeTime;
	/*��������*/
	int numberOfLines;
	/*��������*/
	int numberOfSamples;
	/*ÿ��burst����*/
	int linesPerBurst;
	/*ÿ�����ݸ���*/
	int samplesPerBurst;
	/*burst����*/
	int burstCount;

	/*���ǣ��״����*/
	string sensor;
	/*������ʽ*/
	string polarization;
	/*�Ӵ�����*/
	string swath;
	/*������*/
	string pass;
	/*Heading*/
	double headingAngle;



	/*ÿ��burst��λ��ο�ʱ�䣨range_dependent��*/
	Mat referenceTime;
	bool isReferenceTimeAvailable;
	/*ÿ��burst����������Ƶ�ʣ�range_dependent��*/
	Mat dopplerCentroid;
	bool isDopplerCentroidAvailable;
	/*ÿ��burst�����յ�Ƶ�ʣ�range_dependent��*/
	Mat rangeDependDopplerRate;
	bool isRangeDependDopplerRateAvailiable;
	/*��λ���Ƶ�ʹ�������*/
	Mat AzimuthFmRateList;
	/*����������Ƶ�ʹ�������*/
	Mat DcEstimateList;
	/*ÿ��burst��һ�з�λ��ʱ��*/
	Mat burstAzimuthTime;
	/*ÿ��burstÿ�е�һ����Ч��������*/
	Mat firstValidSample;
	/*ÿ��burstÿ�����һ����Ч��������*/
	Mat lastValidSample;
	/*ÿ��burst��һ����Ч��������*/
	Mat firstValidLine;
	/*ÿ��burst���һ����Ч��������*/
	Mat lastValidLine;
	/*antennaPattern_slantRangeTime*/
	Mat antennaPattern_slantRangeTime;
	/*antennaPattern_elevationAngle*/
	Mat antennaPattern_elevationAngle;
	/*������Ƶ�*/
	Mat geolocationGridPoint;
	/*ÿ��burst���ܶ������ʣ���Ƶ�ʼ�ɨƵ�ʣ�*/
	Mat dopplerRate;
	bool isDopplerRateAvailable;
	/*���ԭʼ����*/
	Mat orbitList;
	/*����ԭʼ�������*/
	Mat preciseOrbitList;


	/*�������*/
	orbitStateVectors* stateVectors;
	/*h5�ļ�*/
	string h5File;


	/*burstƫ����*/
	int burstOffset;

	bool bInitialized;
	char m_xmlFileName[2048];
	char error_head[256];
};

/*--------------------------------------------------*/
/*              �ڱ�һ�ź�����������׼            */
/*--------------------------------------------------*/
class InSAR_API Sentinel1BackGeocoding
{
public:
	Sentinel1BackGeocoding();
	~Sentinel1BackGeocoding();
	/*@brief ��ʼ��������������׼
	* @param h5Files                       �ڱ�һ��ԭʼ�����ļ�
	* @param outFiles                      �����������ļ�
	* @param DEMPath                       DEM�ļ�·��
	* @param masterIndex                   ��Ӱ�����
	* @return �ɹ�����0�����򷵻�-1
	*/
	int init(
		vector<string>& h5Files,
		vector<string>& outFiles,
		const char* DEMPath,
		int masterIndex
	);
	/*@brief �����ڱ�һ������
	* @param h5Files                       �ڱ�һ��ԭʼ�����ļ�
	* @return �ɹ�����0�����򷵻�-1
	*/
	int loadData(vector<string>& h5Files);
	/*@brief ����DEM�ļ�·��
	* @param DEMPath                       DEM�ļ�·��
	* @return �ɹ�����0�����򷵻�-1
	*/
	int setDEMPath(const char* DEMPath);
	/*@brief �������ָ߳�ģ��
	* @param filepath                      �ļ�·��
	* @param lonMin                        ��С����
	* @param lonMax                        ��󾭶�
	* @param latMin                        ��Сγ��
	* @param latMax                        ���γ��
	* @return �ɹ�����0�����򷵻�-1
	*/
	int loadDEM(
		const char* filepath,
		double lonMin,
		double lonMax,
		double latMin,
		double latMax
	);
	/*@brief ���ش����������ļ�
	* @param outFiles                     �����������ļ�
	* @return �ɹ�����0�����򷵻�-1
	*/
	int loadOutFiles(vector<string>& outFiles);
	/*@brief ׼����������ļ�
	* @return �ɹ�����0�����򷵻�-1
	*/
	int prepareOutFiles();
	/*@brief ������Ӱ��
	* @param masterIndex                  ��Ӱ�����
	* @return �ɹ�����0�����򷵻�-1
	*/
	int setMasterIndex(int masterIndex);



	/*@brief ��������ͼ��֮���burstƫ����
	* @return �ɹ�����0�����򷵻�-1
	*/
	int computeBurstOffset();
	/*@brief ȥбȥģ����
	* @param derampDemodPhase                 бģ��λ
	* @param slc                              ��ͼ������
	* @return �ɹ�����0�����򷵻�-1
	*/
	int performDerampDemod(
		Mat& derampDemodPhase,
		ComplexMat& slc
	);
	/*@brief ����DEM��ͶӰ��SAR��ͼ���е�λ��
	* @param slaveImageIndex                       ��ͼ�����
	* @param mBurstIndex                           ��ͼ��burst���
	* @return �ɹ�����0�����򷵻�-1
	*/
	int computeSlavePosition(
		int slaveImagesIndex,
		int mBurstIndex
	);
	/*@brief ���㸨ͼ��ƫ��
	* @param slaveAzimuthOffset                    ��ͼ��λ��ƫ��
	* @param slaveRangeOffset                      ��ͼ�������ƫ��
	* @return �ɹ�����0�����򷵻�-1
	*/
	int computeSlaveOffset(Mat& slaveAzimuthOffset, Mat& slaveRangeOffset);
	/*@brief ��ϸ�ͼ��ƫ�ƣ�1����ϣ�offset = a0 + a1 * x + a2 * y��
	* @param slaveOffset                           ƫ����
	* @param a0                                    ���ϵ��
	* @param a1                                    ���ϵ��
	* @param a2                                    ���ϵ��
	* @return �ɹ�����0�����򷵻�-1
	*/
	int fitSlaveOffset(
		Mat& slaveOffset,
		double* a0,
		double* a1,
		double* a2
	);
	/*@brief ��ͼ��˫���Բ�ֵ�ز�����inplace��ԭ�ز�����
	* @param slc                                   ���ز���ͼ��ԭ�ز�����
	* @param dstHeight                             �ز���ͼ��߶�
	* @param dstWidth                              �ز���ͼ����
	* @param a0Rg                                  ������ƫ�����ϵ��
	* @param a1Rg                                  ������ƫ�����ϵ��
	* @param a2Rg                                  ������ƫ�����ϵ��
	* @param a0Az                                  ��λ��ƫ�����ϵ��
	* @param a1Az                                  ��λ��ƫ�����ϵ��
	* @param a2Az                                  ��λ��ƫ�����ϵ��
	* @return �ɹ�����0�����򷵻�-1
	*/
	int performBilinearResampling(
		ComplexMat& slc,
		int dstHeight,
		int dstWidth,
		double a0Rg, double a1Rg, double a2Rg,
		double a0Az, double a1Az, double a2Az
	);
	/*@brief ��ͼ��˫���Բ�ֵ�ز���
	* @param mBurstIndex                           ��ͼ��burst���
	* @param slaveImageIndex                       ��ͼ�����
	* @param slaveSLC                              �ز�����ĸ�ͼ������
	* @return �ɹ�����0�����򷵻�-1
	*/
	int slaveBilinearInterpolation(
		int mBurstIndex,
		int slaveImageIndex,
		ComplexMat& slaveSLC
	);
	/*@brief ����deburst��Ϣ
	* @return �ɹ�����0�����򷵻�-1
	*/
	int deBurstConfig();
	/*@brief ������������׼
	* @return �ɹ�����0�����򷵻�-1
	*/
	int backGeoCodingCoregistration();

public:

	/*Ӱ������*/
	int numOfImages;
	/*��Ӱ�����*/
	int masterIndex;
	/*�ڱ�һ������*/
	vector<Sentinel1Utils*> su;
	/*�����������ļ�*/
	vector<string> outFiles;
	/*���ָ߳�ģ��*/
	DigitalElevationModel* dem;
	/*���ָ߳�ģ��·��*/
	string DEMPath;
	/*DEMͶӰ����ͼ��ķ�λ������*/
	Mat masterAzimuth;
	/*DEMͶӰ����ͼ��ľ���������*/
	Mat masterRange;
	/*DEMͶӰ����ͼ��ķ�λ������*/
	Mat slaveAzimuth;
	/*DEMͶӰ����ͼ��ľ���������*/
	Mat slaveRange;
	/*DEM��ͶӰ����ͼ��������Ƿ�������*/
	bool isMasterRgAzComputed;

	/*deburst����*/
	Mat start;
	/*deburst����*/
	Mat end;
	/*deburst����*/
	int deburstLines;
	/*burst������Ϣ�Ƿ�������*/
	bool isdeBurstConfig;

	/*��Ч���꣨-1.0��*/
	double invalidRgAzIndex = -1.0;
	/*��Чƫ������-9999.0��*/
	double invalidOffset = -9999.0;
	bool burstOffsetComputed;
	char error_head[256];

};




















#endif // !__FORMATCONVERSION__H__


