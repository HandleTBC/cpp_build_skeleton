#include <string>
#include <array>
#include <vector>

#include <vtkNew.h>
#include <vtkCellArray.h>
#include <vtkPoints.h>
#include <vtkPolyData.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkProperty.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>


class Renderer {
public:
    Renderer(const std::string& window_name) {
        render_window->SetWindowName(window_name.c_str());
        render_window->AddRenderer(renderer);

        render_window_interactor->SetRenderWindow(render_window);
    }

    void start() {
        render_window->Render();
        render_window_interactor->Start();
    }

    void add_points(
        const std::vector<std::array<double, 3>>& input_points
    ){
        //// Geometry and topology
        //  Geometry of a point (coordinate)
        vtkNew<vtkPoints> points;
        
        // Topology of the point (vertex)
        vtkNew<vtkCellArray> vertices;

        // Poldata container
        vtkNew<vtkPolyData> points_data;

        // construct point information
        vtkIdType point_id[1];
        for (size_t ii = 0; ii < input_points.size(); ++ii) {
            point_id[0] = points->InsertNextPoint(input_points[ii].data());
            vertices->InsertNextCell(1, point_id);
        }

        points_data->SetPoints(points);
        points_data->SetVerts(vertices);

        //// Visualize
        vtkNew<vtkPolyDataMapper> mapper;
        mapper->SetInputData(points_data);

        vtkNew<vtkActor> actor;
        actor->SetMapper(mapper);
        actor->GetProperty()->SetColor(255, 0, 0);
        actor->GetProperty()->SetPointSize(20);

        this->renderer->AddActor(actor);
    }

private:
    vtkNew<vtkRenderer> renderer;
    vtkNew<vtkRenderWindow> render_window;
    vtkNew<vtkRenderWindowInteractor> render_window_interactor;
};