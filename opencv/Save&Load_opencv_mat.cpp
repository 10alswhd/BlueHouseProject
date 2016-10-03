bool writeMatBinary(std::ofstream& ofs, const cv::Mat& out_mat) 
 { 
 	if (!ofs.is_open()){ 
 		return false; 
 	} 
 	if (out_mat.empty()){ 
 		int s = 0; 
 		ofs.write((const char*)(&s), sizeof(int)); 
		return true; 
 	} 
 	int type = out_mat.type(); 
 	ofs.write((const char*)(&out_mat.rows), sizeof(int)); 
 	ofs.write((const char*)(&out_mat.cols), sizeof(int)); 
 	ofs.write((const char*)(&type), sizeof(int)); 
 	ofs.write((const char*)(out_mat.data), out_mat.elemSize() * out_mat.total()); 
 
 
 	return true; 
 } 
 
 
 bool readMatBinary(std::ifstream& ifs, cv::Mat& in_mat) 
 { 
 	if (!ifs.is_open()){ 
 		return false; 
 	} 
 
 
 	int rows, cols, type; 
 	ifs.read((char*)(&rows), sizeof(int)); 
 
 
 	if (rows == 0){ 
 		return true; 
 	} 
 	ifs.read((char*)(&cols), sizeof(int)); 
 	ifs.read((char*)(&type), sizeof(int)); 
 
 
 	in_mat.release(); 
 	in_mat.create(rows, cols, type); 
 	ifs.read((char*)(in_mat.data), in_mat.elemSize() * in_mat.total()); 
 
 
 	return true; 
 } 
