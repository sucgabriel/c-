#include "printer.hxx"

Printer::Printer(char* filename) {
    this->file = std::ofstream(filename, std::ios_base::out);
}

void Printer::generate_file(AbstractUni* univ) {

}

inline void Printer::print_balise(char* balise_name) {
    this->file << "<" << balise_name << ">\n";
}

void Printer::print_VTK() {
    print_balise("VTKFile type=\"UnstructuredGrid\" version=\"0.1\" byte_order=\"LittleEndian\"");
}
void Printer::print_grid() {
    print_balise("UnstructuredGrid");
}
void Printer::print_piece(int n) {

    this->file << "<Piece NumberOfPoints=\"" << n << "\n NumberOfCells=\"0\">\n";
}
void Printer::print_points() {
    print_balise("Points");
}
void Printer::print_data_array(char* name, int n) {
    this->file << "DataArray name=\"" << name << 
    "\" type=\"Float32\" NumberOfComponents=\"" << n << "\" format=\'ascii\">\n";
}
void Printer::print_point_data() {
    print_balise("PointData Vectors=\"vector\">");
}
void Printer::print_cells() {
    print_balise("Cells");
}

void Printer::print_VTK_end() {
    print_balise("/VTKFile");
}
void Printer::print_grid_end() {
    print_balise("/UnstructuredGrid");
}
void Printer::print_piece_end() {
    print_balise("/Piece");
}
void Printer::print_points_end() {
    print_balise("/Points");
}
void Printer::print_data_array_end() {
    print_balise("/DataArray");
}
void Printer::print_point_data_end() {
    print_balise("/PointData");
}
void Printer::print_cells_end() {
    print_balise("/Cells");
}


void Printer::print_header_file() {

}
void Printer::print_footer_file() {

}