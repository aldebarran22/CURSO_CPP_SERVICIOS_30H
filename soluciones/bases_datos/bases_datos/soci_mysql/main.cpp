#include <soci/soci.h>
#include <soci/mysql/soci-mysql.h>
#include <iostream>

void test1() {
    try {
        soci::session sql(soci::mysql, "db=empresa3 user=antonio password=antonio host=127.0.0.1 port=3306");

        int count;
        sql << "SELECT COUNT(*) FROM empleados", soci::into(count);
        std::cout << "Número de empleados: " << count << std::endl;
    }
    catch (const std::exception& e) {
        std::cerr << "Error al conectar con MySQL: " << e.what() << std::endl;
    }
}

int main() {
    test1();
    return 0;
}
