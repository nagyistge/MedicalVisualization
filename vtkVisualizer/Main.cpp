//A. Guayaquil
//10.2015

/// VTK library
#include <vtkInteractorStyleTrackballCamera.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkPolyDataMapper.h>
#include <vtkSphereSource.h>
#include <vtkSmartPointer.h>
#include <vtkRenderWindow.h>
#include <vtkConeSource.h>
#include <vtkRenderer.h>
#include <vtkCamera.h>
#include <vtkActor.h>

/// C++ handlers
#include <vector>

namespace gg
{
	class vtkRenderScene
	{
	protected:
		void addSphere()
		{
			vtkSmartPointer<vtkPolyDataMapper> mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
			vtkSmartPointer<vtkSphereSource> sphere = vtkSmartPointer<vtkSphereSource>::New();
			vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();

			mapper->SetInputConnection(sphere->GetOutputPort());
			actor->SetMapper(mapper);

			m_actors.push_back(actor);
		}

		inline std::vector<vtkSmartPointer<vtkActor>> getVectorActors() const
		{
			return m_actors;
		}

		std::vector<vtkSmartPointer<vtkActor>> m_actors;
	};

	class vtkRenderInterface
		: protected vtkRenderScene
	{
	public:
		vtkRenderInterface()
		{
			init();
		}

		void run()
		{
			auto style = vtkSmartPointer<vtkInteractorStyleTrackballCamera>::New();
			m_renderWindowInteractor->SetInteractorStyle(style);

			m_renderWindowInteractor->Initialize();
			m_renderWindowInteractor->Start();
		}

	protected:
		void init()
		{
			auto renderWindow = vtkSmartPointer<vtkRenderWindow>::New();
			auto renderer = vtkSmartPointer<vtkRenderer>::New();

			vtkRenderScene::addSphere();
			auto actors = vtkRenderScene::getVectorActors();
			for (auto & actor : actors)
			{
				renderer->AddActor(actor);
			}

			renderer->SetBackground(1.0, 1.0, 1.0);
			renderWindow->AddRenderer(renderer);
			renderWindow->FullScreenOn();
			m_renderWindowInteractor->SetRenderWindow(renderWindow);
		}

	private:
		vtkSmartPointer<vtkRenderWindowInteractor> m_renderWindowInteractor 
			= vtkSmartPointer<vtkRenderWindowInteractor>::New();
		vtkRenderScene m_renderScene;
	};
}


int main(int argc, char ** argv)
{
	//gg::vtkRenderInterface app;
	//app.run();

	return EXIT_SUCCESS;
}